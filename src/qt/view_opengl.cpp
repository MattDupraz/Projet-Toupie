#include "view_opengl.h"
#include "vertex_shader.h"
#include "system.h"

#include "math_utils.h"
#include "math.h"

void ViewOpenGL::init() {
	// Charge les shaders qui s'occupent de l'affichage
	// Les fichiers sont accessibles avec l'addresse virtuelle qui
	// commence avec un :/
	// Ceci est permi grace au systeme de resources de Qt.
	// Les fichiers accessibles de cette facon sont dans /res
	// et referenties dans le fichier /res/resources.qrc
	prog.addShaderFromSourceFile(QOpenGLShader::Vertex,
			":/vertex_shader.glsl");
	prog.addShaderFromSourceFile(QOpenGLShader::Fragment,
			":/fragment_shader.glsl");

	// Attribue une ID unique aux attributs qu'on veux transmettre
	// aux shaders, voir vertex_shader.h
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
	// qui sont pas de face (regle de la main droite pour
	// l'ordre des coins du triangle = "vertex")
	glEnable(GL_CULL_FACE);

	prog.setUniformValue("lightPos", 0.0, 30.0, 5.0);
	prog.setUniformValue("lightColor", 1.0, 1.0, 1.0);
}

void ViewOpenGL::draw(System const& system) {
	QMatrix4x4 viewMatrix;
	viewMatrix.rotate(-cameraPitch, 1.0, 0.0, 0.0);
	viewMatrix.rotate(-cameraYaw, 0.0, 1.0, 0.0);
	viewMatrix.translate(-cameraPos[0], -cameraPos[1], -cameraPos[2]);
	prog.setUniformValue("view", viewMatrix);

	if (drawFloor) {
		QMatrix4x4 modelMatrix;
		prog.setUniformValue("model", modelMatrix);

		glBegin(GL_QUADS);
		prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0);
		for (int x(-20); x < 20; x++) {
			for (int y(-20); y < 20; y++) {
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

	for (std::size_t i(0); i < system.size(); ++i) {
		system.getTop(i).draw();
	}
}

void ViewOpenGL::rotateCamera(double yaw, double pitch) {
	cameraYaw += yaw;
	cameraPitch += pitch;
	if (cameraPitch > 90.0) cameraPitch = 90.0;
	if (cameraPitch < -90.0) cameraPitch = -90.0;
}

void ViewOpenGL::translateCamera(Vector diff) {
	cameraPos += Vector {
		cos(toRadians(cameraYaw)) * diff[0] + sin(toRadians(cameraYaw)) * diff[2],
		diff[1],	
		cos(toRadians(cameraYaw)) * diff[2] - sin(toRadians(cameraYaw)) * diff[0],
	};
}

void ViewOpenGL::draw(SimpleCone const& top) {
	QMatrix4x4 modelMatrix;
	Vector A(top.getOrigin());
	modelMatrix.translate(A[0], A[1], A[2]);

	modelMatrix.rotate(toDegrees(top.psi()), 0.0, 1.0, 0.0);
	modelMatrix.rotate(toDegrees(top.theta()), 1.0, 0.0, 0.0);
	modelMatrix.rotate(toDegrees(top.phi()), 0.0, 1.0, 0.0);
	
	// Assigne la matrice de translation a la valeur uniforme pour
	// l'acceeder depuis le shader
	prog.setUniformValue("model", modelMatrix);


	double R(top.getRadius());
	double L(top.getHeight());

	uint sides(50);
	double sideAngle(2 * M_PI / sides);
	glBegin(GL_TRIANGLES);
	for (uint i(0); i < sides; i++) {
		Vector v1 {R * cos(sideAngle * i), L, R * sin(sideAngle * i)};
		Vector v2 {R * cos(sideAngle * (i + 1)), L, R * sin(sideAngle * (i + 1))};	
		Vector n = ~(v1 ^ v2);
		
		double red(1.0);
		double green(0.4 + cos(sideAngle * i) * 0.4);
		double blue(0.0);
		prog.setAttributeValue(aColor, red, green, blue);
		
		prog.setAttributeValue(aNormal, n[0], n[1], n[2]);

		prog.setAttributeValue(aVertex, 0.0, 0.0, 0.0);
		prog.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);

		//prog.setAttributeValue(aColor, 0.9, 0.9, 0.9); // noir

		prog.setAttributeValue(aNormal, 0.0, 1.0, 0.0);

		prog.setAttributeValue(aVertex, 0.0, L, 0.0);
		prog.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);
		prog.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
	}
	glEnd();
}


