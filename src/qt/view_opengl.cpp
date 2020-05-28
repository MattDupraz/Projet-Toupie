#include "view_opengl.h"
#include "vertex_shader.h"
#include "system.h"

#include "math_utils.h"
#include "math.h"

#include "tops.h"

ViewOpenGL::ViewOpenGL()
	: shouldDrawFloor(true),
	shouldDrawTrajectories(true),
	shouldDrawBasis(false),
	cameraYaw(0.0),
	cameraPitch(-20.0),
	cameraPos(0.0, 0.4, 5.0),
	cameraFollow(false),
	cameraRotateWithTop(false),
	followedTop(0),
	cone(25),
	cylinder(25),
	circle(25),
	sphere(10, 25)
{}

void ViewOpenGL::init() {
	// Charge les shaders qui s'occupent de l'affichage
	// Les fichiers sont accessibles avec l'addresse virtuelle
	// prefixee par ":/"
	// (c.f. https://doc.qt.io/qt-5/resources.html)
	// Les fichiers accessibles de cette facon sont dans /res
	// et referenties dans le fichier /res/resources.qrc
	prog.addShaderFromSourceFile(QOpenGLShader::Vertex,
			":/vertex_shader.glsl");
	prog.addShaderFromSourceFile(QOpenGLShader::Fragment,
			":/fragment_shader.glsl");

	// Attribue une ID unique aux attributs qu'on veux transmettre
	// aux shaders, voir vertex_shader.h et res/vertex_shader.glsl
	prog.bindAttributeLocation("aPos", aPos);
	prog.bindAttributeLocation("aColor", aColor);
	prog.bindAttributeLocation("aNormal", aNormal);

	// Compile les shaders
	prog.link();
	prog.bind();

	// GL_DEPTH_TEST permet de cacher
	// les objets dessines en arriere plan
	glEnable(GL_DEPTH_TEST);


	// GL_CULL_FACE permet de ne pas dessiner les triangles
	// qui sont pas "de face" (regle de la main gauche pour
	// l'ordre des coins du triangle = "vertex")
	glEnable(GL_CULL_FACE);

	// GL_CLIP_DISTANCE0 ajoute la fonctionalité de découpage
	// par rapport à la distance, voir vertex_shader.glsl
	glEnable(GL_CLIP_DISTANCE0);

	glEnable(GL_FRAMEBUFFER_SRGB);

	// Lie les valeurs uniformes au programme
	u_projection.bind(&prog, "projection");
	u_view.bind(&prog, "view");
	u_translation.bind(&prog, "translation");
	u_model.bind(&prog, "model");
	u_clipMaxY.bind(&prog, "clipMaxY", 1.0e6f);
	u_clipMinY.bind(&prog, "clipMinY", -1.0e6f);
	u_lightPos.bind(&prog, "lightPos", QVector3D(0.0f, 20.0f, 0.0f));
	u_lightColor.bind(&prog, "lightColor", QVector3D(1.0f, 1.0f, 1.0f));
	u_viewPos.bind(&prog, "viewPos");

	// Initialise les modèles à dessiner
	cone.initialize(prog);
	cylinder.initialize(prog);
	circle.initialize(prog);
	sphere.initialize(prog);
}

void ViewOpenGL::draw(System const& system) {
	updateView(system);
	resetUniforms();

	// Dessine le sol
	if (shouldDrawFloor)
		drawFloor();
	// Dessine les trajectoires des toupies
	if (shouldDrawTrajectories)
		drawTrajectories();
	// Dessine la base du systeme de coordonnees
	if (shouldDrawBasis)
		drawBasis();

	// Dessine les toupies du systeme
	for (std::size_t i(0); i < system.size(); ++i) {
		Top const& top(system.getTop(i)); 
		updateUniforms(top);
		// Ajoute le centre de masse a la trajectoire
		Vector A = top.getPosA();
		Vector G = top.getPosG();
		addToTrajectory(trajectoriesCM[top.objectID], QVector3D(G[1], G[2], G[0]));
		addToTrajectory(trajectoriesA[top.objectID], QVector3D(A[1], A[2] + 0.01, A[0]));
		top.draw();
	}
}

void ViewOpenGL::drawBasis() {
	// Axe X
	prog.setAttributeValue(aColor, 1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	prog.setAttributeValue(aPos, 0.0, 0.01, 0.0);
	prog.setAttributeValue(aPos, 0.0, 0.01, 1.0);
	glEnd();
	// Axe Y
	prog.setAttributeValue(aColor, 0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	prog.setAttributeValue(aPos, 0.0, 0.01, 0.0);
	prog.setAttributeValue(aPos, 1.0, 0.01, 0.0);
	glEnd();
	// Axe Z
	prog.setAttributeValue(aColor, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	prog.setAttributeValue(aPos, 0.0, 0.01, 0.0);
	prog.setAttributeValue(aPos, 0.0, 1.01, 0.0);
	glEnd();
}

// Methode pour modifier l'orientation de la camera
void ViewOpenGL::rotateCamera(double yaw, double pitch) {
	cameraYaw += yaw;
	cameraPitch += pitch;
	if (cameraPitch > 90.0) cameraPitch = 90.0;
	if (cameraPitch < -90.0) cameraPitch = -90.0;
}

// Methode pour modifier la position de la camera
void ViewOpenGL::translateCamera(Vector diff) {
	// La translation horizontalle depend de l'orientation de la camera
	cameraPos += QVector3D(
		cos(math::toRadians(cameraYaw)) * diff[0] + sin(math::toRadians(cameraYaw)) * diff[2],
		diff[1],	
		cos(math::toRadians(cameraYaw)) * diff[2] - sin(math::toRadians(cameraYaw)) * diff[0]
		);
}

// Ajoute un vecteur a la trajectoire d'une toupie
void ViewOpenGL::addToTrajectory(std::vector<QVector3D>& v, QVector3D vec) {
	// Ajoute le vecteur ssi la difference avec le dernier vecteur
	// ajoute est assez large
	if (v.empty() || (v.back() - vec).lengthSquared() > 0.00001) {
		v.push_back(vec);

		// Assure que la trajectoire ne soit pas trop longue
		int diff(v.size() - maxTrajectoryLength);
		if (diff > 0) {
			v.erase(v.begin(), v.begin() + diff);
		}
	}
}

// Dessine un GL_LINE_STRIP avec la couleur choisie
void ViewOpenGL::drawTrajectory(std::vector<QVector3D> const& trajectory, QVector3D const& color) {
		prog.setAttributeValue(aColor, color); // couleur de la trajectoire
		glBegin(GL_LINE_STRIP); // "Chaine" de lignes
		for (const QVector3D& vec : trajectory) {
			prog.setAttributeValue(aPos, vec);
		}
		glEnd();
}

// Dessine les trajectoires de la toupie
void ViewOpenGL::drawTrajectories() {
	// Reinitialise la matrice de transformation du modele a l'identite
	// (pas de transformation)
	for (const auto& entry : trajectoriesCM) {
		drawTrajectory(entry.second, QVector3D(1.0, 0.0, 0.0));
	}
	for (const auto& entry : trajectoriesA) {
		drawTrajectory(entry.second, QVector3D(0.0, 0.0, 1.0));
	}
}

// Dessine le sol
void ViewOpenGL::drawFloor() {
	glBegin(GL_QUADS);
	prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0); // Le vecteur normal du sol pour l'eclairage
	// On décale le sol de la position de la caméra pour tricher un sol infini
	int cameraX = int(cameraPos.x());
	int cameraY = int(cameraPos.z());
	int size(30);
	// Ceci n'est pas une super methode - il faudrait mieux faire un shader et faire l'echiquier dans le fragment shader
	// plutôt que ici ca permetterait de réduire pas mal le nombre d'objets déssinés
	for (int x(-size + cameraX); x < (size + cameraX); x++) {
		for (int y(-size + cameraY); y < (size + cameraY); y++) {
			// Alterne un gris fonce et clair pour faire un pattern
			// d'echiquier
			double brightness(((x + y) % 2) ? 0.5 : 0.25);
			prog.setAttributeValue(aColor, brightness, brightness, brightness);

			prog.setAttributeValue(aPos, double(x), 0.0, double(y));
			prog.setAttributeValue(aPos, double(x), 0.0, double(y + 1));
			prog.setAttributeValue(aPos, double(x + 1), 0.0, double(y + 1));
			prog.setAttributeValue(aPos, double(x + 1), 0.0, double(y));
		}
	}
	glEnd();
}

// Commence à suivre la toupie suivante
void ViewOpenGL::followNext(bool rotate) {
	cameraFollow = true;
	cameraRotateWithTop = rotate;
	++followedTop;
}

// Arrète de suivre de toupie
void ViewOpenGL::stopFollow() {
	cameraFollow = false;
}

// Emploie la matrice de projection choisie
void ViewOpenGL::setProjection(QMatrix4x4 const& matrix) {
	u_projection.setValue(matrix);
	u_projection.update();
}

// Réinitialize les matrices de transformations de l'objet
void ViewOpenGL::resetUniforms() {
	u_translation.reset();
	u_translation.update();
	u_model.reset();
	u_model.update();
}

// Initialize la matrice de vue
void ViewOpenGL::updateView(System const& system) {
	u_view.reset();
	u_view.value().rotate(-cameraPitch, 1.0, 0.0, 0.0);
	u_view.value().rotate(-cameraYaw, 0.0, 1.0, 0.0);
	if (cameraFollow) {
		// Positionne la caméra de manière qu'elle regarde directement la toupie
		Top const& top(system.getTop(followedTop % system.size())); 

		Vector posG(top.getPosG());
		QVector3D absolute(posG[1], posG[2], posG[0]); // Les coordonnees physiques et graphiques diffèrent
		// note: On purait ajouter une touche pour controler la distance de la caméra de la toupie
		QVector3D relative(0.0, 0.0, 4.0);
		QMatrix4x4 rotation;

		if (cameraRotateWithTop) { // Met la caméra dans le repère de la toupie (elle tourne avec)
			u_view.reset();
			u_view.value().rotate(-math::toDegrees(top.theta()), 0.0, 0.0, 1.0);
			u_view.value().rotate(-math::toDegrees(top.psi()), 0.0, 1.0, 0.0);

			rotation.rotate(math::toDegrees(top.psi()), 0.0, 1.0, 0.0);
			rotation.rotate(math::toDegrees(top.theta()), 0.0, 0.0, 1.0);
		} else { // Sinon oriente la caméra selon son orientation précedente
			rotation.rotate(cameraYaw, 0.0, 1.0, 0.0);
			rotation.rotate(cameraPitch, 1.0, 0.0, 0.0);
		}

		relative = rotation * relative;
		cameraPos = absolute + relative;
	}
	u_view.value().translate(-cameraPos);
	u_view.update();

	u_viewPos.setValue(cameraPos);
	u_viewPos.update();
}

// Initialize les matrices du modèle en fonction de la position
// et orientation de la toupie
void ViewOpenGL::updateUniforms(Top const& top) {
	// Initialize la matrice de translation pour cette toupie
	u_translation.reset();
	// z est négatif pour suivre la règle de la main droite
	u_translation.value().translate(top.y(), top.z(), top.x()); // Les coordonees physiques et graphiques diffèrent
	u_translation.update();

	// Matrice de rotation à partir des angles d'euler
	u_model.reset();
	u_model.value().rotate(math::toDegrees(top.psi()), 0.0, 1.0, 0.0);
	u_model.value().rotate(math::toDegrees(top.theta()), 0.0, 0.0, 1.0);
	u_model.value().rotate(math::toDegrees(top.phi()), 0.0, 1.0, 0.0);
	u_model.update();
}

// Dessine le cone
void ViewOpenGL::draw(SimpleCone const& top) {
	// Valeurs specifiques au cone
	double R(top.getRadius());
	double L(top.getHeight());

	u_model.value().scale(R, L, R);
	u_model.update();

	cone.draw();
}


void ViewOpenGL::draw(Gyroscope const& top) {
	double R(top.getRadius());
	double L(top.getThickness());
	double d(top.getHeight());


	// Tige qui "supporte" le disque en rotation
	glLineWidth(3.0);
	glBegin(GL_LINES);
	prog.setAttributeValue(aColor, 0.0, 0.0, 1.0);
	prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0);
	prog.setAttributeValue(aPos, 0.0, 0.0, 0.0);
	prog.setAttributeValue(aPos, 0.0, 2 * d, 0.0);
	glEnd();

	// On dessine le modèle
	u_translation.value().translate(u_model.value() * QVector3D(0, d, 0));
	u_translation.update();
	u_model.value().scale(R, 0.5f * L, R);
	u_model.update();

	cylinder.draw();
}

void ViewOpenGL::draw(GeneralTop const& top) {
	QMatrix4x4 model(u_model.value());

	// On dessine le modèle
	for (unsigned int i(0); i < top.getLayers().size(); ++i) {
		double h = (2*i + 1) * 0.5 * top.getThickness();
		double R = top.getLayers()[i];

		updateUniforms(top);
		u_translation.value().translate(model
			* QVector3D(0, h, 0));
		u_translation.update();
		u_model.value().scale(R, 0.5f * top.getThickness(), R);
		u_model.update();
		cylinder.draw();
	}

}

void ViewOpenGL::draw(ChineseTop const& top) {
	// Valeurs specifiques au cone
	double r(sqrt(pow(top.getRadius(), 2) - pow(top.getRadius() - top.getTruncatedHeight(), 2)));
	double R(top.getRadius());
	double L(top.getRadius() - top.getTruncatedHeight());

	u_translation.value().translate(0.0, R, 0.0);
	u_translation.update();

	u_model.value().scale(R);
	u_model.update();

	// On coupe le bout de la sphère (pour la tronquer)
	// ceci est par rapport au modèle non-transformé
	// c.f. l'implémentation dans le shader
	u_clipMaxY.setValue(float(L));
	u_clipMaxY.update();

	sphere.draw();

	// On enlève le clipPlane
	u_clipMaxY.setValue(10e6f);
	u_clipMaxY.update();

	u_model.value().translate(0.0, L, 0.0);
	u_model.value().scale(r/R);
	u_model.update();

	circle.draw();
}
