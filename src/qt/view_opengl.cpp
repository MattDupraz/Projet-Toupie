#include "view_opengl.h"
#include "vertex_shader.h"
#include "system.h"

#include "math_utils.h"
#include "math.h"

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
	prog.bindAttributeLocation("aVertex", aVertex);
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

	// Definie la position et couleur de la source de lumiere
	prog.setUniformValue("lightPos", 0.0, 30.0, 5.0);
	prog.setUniformValue("lightColor", 1.0, 1.0, 1.0);
}

void ViewOpenGL::draw(System const& system) {
	// viewMatrix est la transformation du monde par rapport
	// a la position et orientation de la camera
	QMatrix4x4 viewMatrix;
	viewMatrix.rotate(-cameraPitch, 1.0, 0.0, 0.0);
	viewMatrix.rotate(-cameraYaw, 0.0, 1.0, 0.0);
	viewMatrix.translate(-cameraPos[0], -cameraPos[1], -cameraPos[2]);
	prog.setUniformValue("view", viewMatrix);

	// Dessine le sol
	if (shouldDrawFloor)
		drawFloor();
	// Dessine les trajectoires des toupies
	if (shouldDrawTrajectories)
		drawTrajectories();

	// Dessine les toupies du systeme
	for (std::size_t i(0); i < system.size(); ++i) {
		system.getTop(i).draw();
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
void ViewOpenGL::addToTrajectory(unsigned int ID, QVector3D vec) {
	std::vector<QVector3D>& v = trajectories[ID];
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
	prog.setUniformValue("model", QMatrix4x4());
	for (const auto& entry : trajectories) {
		const std::vector<QVector3D>& trajectory = entry.second;
		prog.setAttributeValue(aColor, 1.0, 0.0, 0.0); // couleur de la trajectoire
		glBegin(GL_LINE_STRIP); // "Chaine" de lignes
		for (const QVector3D& vec : trajectory) {
			prog.setAttributeValue(aVertex, vec);
		}
		glEnd();
	}
}

// Dessine le sol
void ViewOpenGL::drawFloor() {
	// Reinitialise la matrice de transformation du modele a l'identite
	// (pas de transformation)
	QMatrix4x4 modelMatrix;
	prog.setUniformValue("model", modelMatrix);

	glBegin(GL_QUADS);
	prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0); // Le vecteur normal du sol pour l'eclairage
	for (int x(-20); x < 20; x++) {
		for (int y(-20); y < 20; y++) {
			// Alterne un gris fonce et clair pour faire un pattern
			// d'echiquier
			double brightness(((x + y) % 2) ? 0.5 : 0.25);
			prog.setAttributeValue(aColor, brightness, brightness, brightness);

			prog.setAttributeValue(aVertex, double(x), 0.0, double(y));
			prog.setAttributeValue(aVertex, double(x), 0.0, double(y + 1));
			prog.setAttributeValue(aVertex, double(x + 1), 0.0, double(y + 1));
			prog.setAttributeValue(aVertex, double(x + 1), 0.0, double(y));
		}
	}
	glEnd();
}

QMatrix4x4 getModelMatrix(Top const& top) {
	// Matrice qui transforme le modele
	// Elle nous permet de dessiner la toupie sans se soucier de la
	// position et orientation de la toupie, ceci est gere dans le vertex shader
	// en appliquant cette matrice de transformation
	QMatrix4x4 modelMatrix;
	
	// Translate la toupie au bon endroit
	modelMatrix.translate(top.x(), top.y(), top.z());

	// Oriente la toupie par rapport aux angles d'euler
	modelMatrix.rotate(toDegrees(top.psi()), 0.0, 1.0, 0.0);
	modelMatrix.rotate(toDegrees(top.theta()), 1.0, 0.0, 0.0);
	modelMatrix.rotate(toDegrees(top.phi()), 0.0, 1.0, 0.0);
	
	return modelMatrix;
}

// Dessine le cone
void ViewOpenGL::draw(SimpleCone const& top) {
	// Matrice de transformation (position, orientation) pour le cone
	QMatrix4x4 modelMatrix(getModelMatrix(top));
	prog.setUniformValue("model", modelMatrix);
	
	// Ajoute le centre de masse a la trajectoire
	addToTrajectory(top.objectID, modelMatrix * QVector3D(0, top.getHeightCM(), 0));

	// Valeurs specifiques au cone
	double R(top.getRadius());
	double L(top.getHeight());

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
		prog.setAttributeValue(aVertex, 0.0, 0.0, 0.0);
		prog.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);

		//prog.setAttributeValue(aColor, 0.9, 0.9, 0.9); // noir

		// Vecteur normal de la base du cone
		prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0);

		// Triangle correspondant a la base du cone
		prog.setAttributeValue(aVertex, 0.0, L, 0.0);
		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);
		prog.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
	}
	glEnd();
}


void ViewOpenGL::draw(Gyroscope const& top) {
	// Matrice de transformation (position, orientation) pour le gyroscope
	QMatrix4x4 modelMatrix(getModelMatrix(top));
	prog.setUniformValue("model", modelMatrix);
	
	// Ajoute le centre de masse a la trajectoire
	addToTrajectory(top.objectID, modelMatrix * QVector3D(0, top.getHeightCM(), 0));

	double R(top.getRadius());
	double L(top.getThickness());
	double d(top.getHeight());

	uint sides(50); // Nombre de cotes du disque
	double sideAngle(2 * M_PI / sides);
	glBegin(GL_TRIANGLES);
	for (uint i(0); i < sides; i++) {
		// Vecteurs de la partie dessine
		Vector u1 {R * cos(sideAngle * i), d - L/2.0, R * sin(sideAngle * i)};
		Vector v1 {R * cos(sideAngle * i), d + L/2.0, R * sin(sideAngle * i)};
		Vector u2 {R * cos(sideAngle * (i + 1)), d - L/2.0, R * sin(sideAngle * (i + 1))};	
		Vector v2 {R * cos(sideAngle * (i + 1)), d + L/2.0, R * sin(sideAngle * (i + 1))};	
		Vector n = ~(Vector{0, -1, 0} ^ (v2 - v1)); // Vecteur normal au cote
		
		// Couleur qui varie avec l'angle
		double red(0.0);
		double green(0.4 + cos(sideAngle * i) * 0.4);
		double blue(1.0);
		prog.setAttributeValue(aColor, red, green, blue);
		
		// Normale de la face du cote
		prog.setAttributeValue(aNormal, n[0], n[1], n[2]);
		// Face du cote du disque
		prog.setAttributeValue(aVertex, u1[0], u1[1], u1[2]);
		prog.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);

		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);
		prog.setAttributeValue(aVertex, u2[0], u2[1], u2[2]);
		prog.setAttributeValue(aVertex, u1[0], u1[1], u1[2]);

		// Normale a la face du haut du disque
		prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0);
		// Face du haut du disque
		prog.setAttributeValue(aVertex, 0.0, d + L/2.0, 0.0);
		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);
		prog.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);

		// Normale a la face du bas du disque
		prog.setAttributeValue(aNormal, 0.0, -1.0, 0.0);
		// Face du bas du disque
		prog.setAttributeValue(aVertex, 0.0, d - L/2.0, 0.0);
		prog.setAttributeValue(aVertex, u1[0], u1[1], u1[2]);
		prog.setAttributeValue(aVertex, u2[0], u2[1], u2[2]);
	}
	glEnd();

	// Tige qui "supporte" le disque en rotation
	glLineWidth(3.0);
	glBegin(GL_LINES);
	prog.setAttributeValue(aVertex, 0.0, 0.0, 0.0);
	prog.setAttributeValue(aVertex, 0.0, 2 * d, 0.0);
	glEnd();
}
