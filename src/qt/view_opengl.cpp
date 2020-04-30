#include "view_opengl.h"
#include "vertex_shader.h"
#include "system.h"

#include "math_utils.h"
#include "math.h"

#include "gl_uniform.h"

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

	uProjection.bind(&prog, "projection");
	uView.bind(&prog, "view");
	uTranslation.bind(&prog, "translation");
	uOrientation.bind(&prog, "orientation");
	uScale.bind(&prog, "scale");

	// Definie la position et couleur de la source de lumiere
	prog.setUniformValue("lightPos", -1.0, 10.0, 2.0);
	prog.setUniformValue("lightColor", 1.0, 1.0, 1.0);

	cone.init_cone(prog, 25);
	disk.init_disk(prog, 25);
}

void ViewOpenGL::draw(System const& system) {
	// viewMatrix est la transformation du monde par rapport
	// a la position et orientation de la camera
	uView.value().setToIdentity();
	uView.value().rotate(-cameraPitch, 1.0, 0.0, 0.0);
	uView.value().rotate(-cameraYaw, 0.0, 1.0, 0.0);
	uView.value().translate(-cameraPos[0], -cameraPos[1], -cameraPos[2]);
	uView.update();

	uTranslation.reset();
	uOrientation.reset();
	uScale.reset();

	// Dessine le sol
	if (shouldDrawFloor)
		drawFloor();
	// Dessine les trajectoires des toupies
	if (shouldDrawTrajectories)
		drawTrajectories();

	// Dessine les toupies du systeme
	for (std::size_t i(0); i < system.size(); ++i) {
		Top const& top(system.getTop(i)); 
		updateTranslation(top);
		updateOrientation(top);
		top.draw();
	}
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
	cameraPos += Vector {
		cos(toRadians(cameraYaw)) * diff[0] + sin(toRadians(cameraYaw)) * diff[2],
		diff[1],	
		cos(toRadians(cameraYaw)) * diff[2] - sin(toRadians(cameraYaw)) * diff[0],
	};
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

// Dessine les trajectoires de la toupie
void ViewOpenGL::drawTrajectories() {
	// Reinitialise la matrice de transformation du modele a l'identite
	// (pas de transformation)
	for (const auto& entry : trajectoriesCM) {
		const std::vector<QVector3D>& trajectory = entry.second;
		prog.setAttributeValue(aColor, 0.0, 0.0, 1.0); // couleur de la trajectoire
		glBegin(GL_LINE_STRIP); // "Chaine" de lignes
		for (const QVector3D& vec : trajectory) {
			prog.setAttributeValue(aPos, vec);
		}
		glEnd();
	}
	for (const auto& entry : trajectoriesA) {
		const std::vector<QVector3D>& trajectory = entry.second;
		prog.setAttributeValue(aColor, 1.0, 0.0, 0.0); // couleur de la trajectoire
		glBegin(GL_LINE_STRIP); // "Chaine" de lignes
		for (const QVector3D& vec : trajectory) {
			prog.setAttributeValue(aPos, vec);
		}
		glEnd();
	}
}

// Dessine le sol
void ViewOpenGL::drawFloor() {
	glBegin(GL_QUADS);
	prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0); // Le vecteur normal du sol pour l'eclairage
	for (int x(-20); x < 20; x++) {
		for (int y(-20); y < 20; y++) {
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

void ViewOpenGL::updateOrientation(Top const& top) {
	uOrientation.value().setToIdentity();
	// Oriente la toupie par rapport aux angles d'euler
	uOrientation.value().rotate(toDegrees(top.psi()), 0.0, 1.0, 0.0);
	uOrientation.value().rotate(toDegrees(top.theta()), 1.0, 0.0, 0.0);
	uOrientation.value().rotate(toDegrees(top.phi()), 0.0, 1.0, 0.0);
	uOrientation.update();
}

void ViewOpenGL::updateTranslation(Top const& top) {
	uTranslation.value().setToIdentity();
	uTranslation.value().translate(top.x(), top.y(), -top.z());
	uTranslation.update();
}

// Dessine le cone
void ViewOpenGL::draw(SimpleCone const& top) {
	
	// Ajoute le centre de masse a la trajectoire
	addToTrajectory(trajectoriesCM[top.objectID], uTranslation.value() * uOrientation.value() * QVector3D(0, top.getHeightCM(), 0));
	addToTrajectory(trajectoriesA[top.objectID], QVector3D(top.x(), 0.05, -top.z()));

	// Valeurs specifiques au cone
	double R(top.getRadius());
	double L(top.getHeight());

	uScale.value().scale(R, L, R);
	uScale.update();

	cone.draw();

	uScale.reset();

}


void ViewOpenGL::draw(Gyroscope const& top) {
	
	// Ajoute le centre de masse a la trajectoire
	addToTrajectory(trajectoriesCM[top.objectID], uTranslation.value() * uOrientation.value() * QVector3D(0, top.getHeightCM(), 0));
	addToTrajectory(trajectoriesA[top.objectID], QVector3D(top.x(), 0.05, -top.z()));

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
	uTranslation.value().translate(uOrientation.value() * QVector3D(0, d, 0));
	uTranslation.update();
	uScale.value().scale(R, 0.5f * L, R);
	uScale.update();

	disk.draw();

	uScale.reset();
}

void ViewOpenGL::draw(ChineseTop const& top) {
	// Ajoute le centre de masse a la trajectoire
	addToTrajectory(trajectoriesCM[top.objectID], uTranslation.value() * uOrientation.value() * QVector3D(0, top.getHeightCM(), 0));
	addToTrajectory(trajectoriesA[top.objectID], QVector3D(top.x(), 0.05, -top.z()));

	// Valeurs specifiques au cone
	double R(sqrt(pow(top.getRadius(), 2) - pow(top.getRadius() - top.getTruncatedHeight(), 2)));
	double L(top.getRadius() - top.getTruncatedHeight());

	uint sides(50); // Nombre de cotes du cone
	double sideAngle(2 * M_PI / sides);
	glBegin(GL_TRIANGLES);
	for (uint i(0); i < sides; i++) {
		// Vecteurs sur la base du cone
		Vector v1 {R * cos(sideAngle * i), L, R * sin(sideAngle * i)};
		Vector v2 {R * cos(sideAngle * (i + 1)), L, R * sin(sideAngle * (i + 1))};	
		// Vecteur normal au triangle du cote du cone
		Vector n = ~(v1 ^ v2);
		
		// Couleur qui varie avec l'angle
		double red(1.0);
		double green(0.4 + cos(sideAngle * i) * 0.4);
		double blue(0.0);
		prog.setAttributeValue(aColor, red, green, blue);
		
		// Assigne le vecteur normal pour l'eclairage
		prog.setAttributeValue(aNormal, n[0], n[1], n[2]);

		// Triangle du cote du cone
		prog.setAttributeValue(aPos, 0.0, 0.0, 0.0);
		prog.setAttributeValue(aPos, v1[0], v1[1], v1[2]);
		prog.setAttributeValue(aPos, v2[0], v2[1], v2[2]);

		//prog.setAttributeValue(aColor, 0.9, 0.9, 0.9); // noir

		// Vecteur normal de la base du cone
		prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0);

		// Triangle correspondant a la base du cone
		prog.setAttributeValue(aPos, 0.0, L, 0.0);
		prog.setAttributeValue(aPos, v2[0], v2[1], v2[2]);
		prog.setAttributeValue(aPos, v1[0], v1[1], v1[2]);
	}
	glEnd();

}
