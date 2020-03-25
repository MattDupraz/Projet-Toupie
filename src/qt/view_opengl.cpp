#include "view_opengl.h"
#include "vertex_shader.h"

#include <iostream>
#include "math_utils.h"

void ViewOpenGL::draw(SimpleCone const& top) {
	// Translate la "camera" par (0, 0, -2.0)
	// (voir /res/vertex_shader.glsl)
	QMatrix4x4 translation_matrix;

	translation_matrix.translate(0.0, 0.0, -5.0);
	std::cout << top.getP()
	  << " " << top.getDP()
  		<< " " << top.getDDP(top.getP(), top.getDP())  << std::endl;
	translation_matrix.rotate(toDegrees(top.psi()), 0.0, 1.0, 0.0);
	translation_matrix.rotate(toDegrees(top.theta()), 1.0, 0.0, 0.0);
	translation_matrix.rotate(toDegrees(top.phi()), 0.0, 1.0, 0.0);
	
	// Assigne la matrice de translation a la valeur uniforme pour
	// l'acceeder depuis le shader
	prog_.setUniformValue("translation", translation_matrix);


	double R(0.5);
	double L(1.5);

	// Debut du dessin, dessine un triangle avec chaque coin
	// qui a une couleur associee (qui est definie au prealable avec
	// ID_COLOR). Les coordonnees du triangle ne sont PAS
	// les coordonnees des pixels sur l'ecran, plutot des coordonnees
	// dans un plan 3D. La camera est placee par rapport aux matrices
	// de projection et translation.
	//
	// Les couleurs sont en format (rouge, vert, bleu)
	// Les coordonnees sont cartesiennes (x, y, z)
	glBegin(GL_QUADS); 
	// face coté Y = +1
	prog_.setAttributeValue(ID_COLOR, 0.0, 0.0, 1.0); // bleu
	prog_.setAttributeValue(ID_VERTEX, -R, L, -R);
	prog_.setAttributeValue(ID_VERTEX, -R, L,  R);
	prog_.setAttributeValue(ID_VERTEX,  R, L,  R);
	prog_.setAttributeValue(ID_VERTEX,  R, L, -R);

	glEnd();

	glBegin(GL_TRIANGLES);
	// face coté Y = -1
	prog_.setAttributeValue(ID_COLOR, 0.0, 1.0, 1.0); // cyan
	prog_.setAttributeValue(ID_VERTEX,  0.0,  0.0,  0.0);
	prog_.setAttributeValue(ID_VERTEX,  R,  L, -R);
	prog_.setAttributeValue(ID_VERTEX,  R,  L,  R);

	// face coté Y = -1
	prog_.setAttributeValue(ID_COLOR, 1.0, 0.0, 0.0); // red
	prog_.setAttributeValue(ID_VERTEX,  0.0,  0.0,  0.0);
	prog_.setAttributeValue(ID_VERTEX, -R, L, -R);
	prog_.setAttributeValue(ID_VERTEX,  R, L, -R);
	// face coté Z = +1
	prog_.setAttributeValue(ID_COLOR, 1.0, 1.0, 0.0); // jaune
	prog_.setAttributeValue(ID_VERTEX,  0.0,  0.0,  0.0);
	prog_.setAttributeValue(ID_VERTEX, -R, L,  R);
	prog_.setAttributeValue(ID_VERTEX, -R, L, -R);

	// face coté Z = -1
	prog_.setAttributeValue(ID_COLOR, 1.0, 0.0, 1.0); // magenta
	prog_.setAttributeValue(ID_VERTEX,  0.0,  0.0,  0.0);
	prog_.setAttributeValue(ID_VERTEX,  R, L,  R);
	prog_.setAttributeValue(ID_VERTEX, -R, L,  R);
	glEnd();
	// Fin de l'affichage du triangle.
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
	prog_.bindAttributeLocation("vertex", ID_VERTEX);
	prog_.bindAttributeLocation("color", ID_COLOR);

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
