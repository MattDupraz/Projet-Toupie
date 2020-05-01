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

	glEnable(GL_CLIP_DISTANCE0);

	u_projection.bind(&prog, "projection");
	u_view.bind(&prog, "view");
	u_translation.bind(&prog, "translation");
	u_model.bind(&prog, "model");

	// Definie la position et couleur de la source de lumiere
	prog.setUniformValue("lightPos", 0.0, 20.0, 0.0);
	prog.setUniformValue("lightColor", 1.0, 1.0, 1.0);

	prog.setUniformValue("clipMaxY",  1.0e6f);
	prog.setUniformValue("clipMinY", -1.0e6f);

	cone.init_cone(prog, 25);
	disk.init_disk(prog, 25);
	sphere.init_sphere(prog, 10, 25);
}

void ViewOpenGL::draw(System const& system) {
	updateView();
	resetUniforms();

	// Dessine le sol
	if (shouldDrawFloor)
		drawFloor();
	// Dessine les trajectoires des toupies
	if (shouldDrawTrajectories)
		drawTrajectories();

	// Dessine les toupies du systeme
	for (std::size_t i(0); i < system.size(); ++i) {
		Top const& top(system.getTop(i)); 
		updateUniforms(top);
		// Ajoute le centre de masse a la trajectoire
		addToTrajectory(trajectoriesCM[top.objectID], u_translation.value() * u_model.value() * QVector3D(0, top.getHeightCM(), 0));
		addToTrajectory(trajectoriesA[top.objectID], QVector3D(top.x(), 0.05, -top.z()));
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
		prog.setAttributeValue(aColor, 1.0, 0.0, 0.0); // couleur de la trajectoire
		glBegin(GL_LINE_STRIP); // "Chaine" de lignes
		for (const QVector3D& vec : trajectory) {
			prog.setAttributeValue(aPos, vec);
		}
		glEnd();
	}
	for (const auto& entry : trajectoriesA) {
		const std::vector<QVector3D>& trajectory = entry.second;
		prog.setAttributeValue(aColor, 0.0, 0.0, 1.0); // couleur de la trajectoire
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

void ViewOpenGL::setProjection(QMatrix4x4 const& matrix) {
	u_projection.setValue(matrix);
	u_projection.update();
}

void ViewOpenGL::resetUniforms() {
	u_translation.reset();
	u_translation.update();
	u_model.reset();
	u_model.update();
}

void ViewOpenGL::updateView() {
	u_view.reset();
	u_view.value().rotate(-cameraPitch, 1.0, 0.0, 0.0);
	u_view.value().rotate(-cameraYaw, 0.0, 1.0, 0.0);
	u_view.value().translate(-cameraPos[0], -cameraPos[1], -cameraPos[2]);
	u_view.update();
}

void ViewOpenGL::updateUniforms(Top const& top) {
	u_translation.reset();
	u_translation.value().translate(top.x(), top.y(), -top.z());
	u_translation.update();

	u_model.reset();
	u_model.value().rotate(toDegrees(top.psi()), 0.0, 1.0, 0.0);
	u_model.value().rotate(toDegrees(top.theta()), 1.0, 0.0, 0.0);
	u_model.value().rotate(toDegrees(top.phi()), 0.0, 1.0, 0.0);
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

	disk.draw();
}

void ViewOpenGL::draw(ChineseTop const& top) {
	// Valeurs specifiques au cone
	double R(sqrt(pow(top.getRadius(), 2) - pow(top.getRadius() - top.getTruncatedHeight(), 2)));
	double L(top.getRadius() - top.getTruncatedHeight());

	u_model.value().scale(R);
	u_model.update();

	glDisable(GL_CULL_FACE);
	prog.setUniformValue("clipMaxY", float(L));

	sphere.draw();

	glEnable(GL_CULL_FACE);
	prog.setUniformValue("clipMaxY", 10e6f);

}
