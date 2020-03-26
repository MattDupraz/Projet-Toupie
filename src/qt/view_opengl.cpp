#include "view_opengl.h"
#include "vertex_shader.h"

#include <iostream>
#include "math_utils.h"
#include "math.h"

void ViewOpenGL::draw(SimpleCone const& top) {
	
	prog_.setUniformValue("lightPos", 0.0, 3.0, 5.0);
	prog_.setUniformValue("lightColor", 1.0, 1.0, 1.0);


	// Translate la "camera" par (0, 0, -2.0)
	// (voir /res/vertex_shader.glsl)
	QMatrix4x4 view_matrix;
	view_matrix.translate(0.0, 0.0, -5.0);
	prog_.setUniformValue("view", view_matrix);

	QMatrix4x4 model_matrix;
	std::cout << top.getP()
	  << " " << top.getDP()
  		<< " " << top.getDDP(top.getP(), top.getDP())  << std::endl;
	model_matrix.rotate(toDegrees(top.psi()), 0.0, 1.0, 0.0);
	model_matrix.rotate(toDegrees(top.theta()), 1.0, 0.0, 0.0);
	model_matrix.rotate(toDegrees(top.phi()), 0.0, 1.0, 0.0);
	
	// Assigne la matrice de translation a la valeur uniforme pour
	// l'acceeder depuis le shader
	prog_.setUniformValue("model", model_matrix);


	double R(0.5);
	double L(1.5);

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
		prog_.setAttributeValue(aColor, red, green, blue);
		
		prog_.setAttributeValue(aNormal, n[0], n[1], n[2]);

		prog_.setAttributeValue(aVertex, 0.0, 0.0, 0.0);
		prog_.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
		prog_.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);

		//prog_.setAttributeValue(aColor, 0.9, 0.9, 0.9); // noir

		prog_.setAttributeValue(aNormal, 0.0, 1.0, 0.0);

		prog_.setAttributeValue(aVertex, 0.0, L, 0.0);
		prog_.setAttributeValue(aVertex, v2[0], v2[1], v2[2]);
		prog_.setAttributeValue(aVertex, v1[0], v1[1], v1[2]);
	}
	glEnd();
}

void ViewOpenGL::init() {
	// Charge les shaders qui s'occupent de l'affichage
	// Les fichiers sont accessibles avec l'addresse virtuelle qui
	// commence avec un :/
	// Ceci est permi grace au systeme de resources de Qt.
	// Les fichiers accessibles de cette facon sont dans /res
	// et referenties dans le fichier /res/resources.qrc
	prog_.addShaderFromSourceFile(QOpenGLShader::Vertex,
			":/vertex_shader.glsl");
	prog_.addShaderFromSourceFile(QOpenGLShader::Fragment,
			":/fragment_shader.glsl");

	// Attribue une ID unique aux attributs qu'on veux transmettre
	// aux shaders, voir vertex_shader.h
	prog_.bindAttributeLocation("aVertex", aVertex);
	prog_.bindAttributeLocation("aColor", aColor);
	prog_.bindAttributeLocation("aNormal", aNormal);

	// Compile les shaders
	prog_.link();
	prog_.bind();

	// GL_DEPTH_TEST permet de cacher
	// les objets dessines en arriere plan
	glEnable(GL_DEPTH_TEST);

	// GL_CULL_FACE permet de ne pas dessiner les triangles
	// qui sont pas de face (regle de la main droite pour
	// l'ordre des coins du triangle = "vertex")
	glEnable(GL_CULL_FACE);
}
