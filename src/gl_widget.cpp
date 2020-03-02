#include <QMatrix4x4>
#include "gl_widget.h"
#include "vertex_shader.h"

// Appelee une fois au debut du programme
void GLWidget::initializeGL() {
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
	prog.bindAttributeLocation("vertex", ID_VERTEX);
	prog.bindAttributeLocation("color", ID_COLOR);

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
}

// Appellee a chaque fois que la taille de la fenetre change
void GLWidget::resizeGL(int width, int height) {
	// Definit la partie de la fenetre pour dessiner
	glViewport(0, 0, width, height);

	// Matrice de projection cree la perspective dans l'affichage
	// (voir /res/vertex_shader.glsl)
	QMatrix4x4 projection_matrix;

	// QMatrix4x4::perspective(float verticalAngle, float aspectRation,
	// 						float nearPlane, float farPlane)
	// Cree la matrice de projection.
	projection_matrix.perspective(70.0,
			width/(height ? height : 1.0), 1e-3, 1e5);

	// Assigne la matrice de projection a la valeur uniforme pour
	// l'utiliser dans le shader
	prog.setUniformValue("projection", projection_matrix);
}

// Appellee a chaque frame
void GLWidget::paintGL() {
	// Reinitialise le buffer de couleur et de profondeur
	// Necessaire pour ne pas avoir de surprises
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Translate la "camera" par (0, 0, -2.0)
	// (voir /res/vertex_shader.glsl)
	QMatrix4x4 translation_matrix;
	translation_matrix.translate(0.0, 0.0, -2.0);
	
	// Assigne la matrice de translation a la valeur uniforme pour
	// l'acceeder depuis le shader
	prog.setUniformValue("translation", viewport_matrix);

	// Debut du dessin, dessine un triangle avec chaque coin
	// qui a une couleur associee (qui est definie au prealable avec
	// ID_COLOR). Les coordonnees du triangle ne sont PAS
	// les coordonnees des pixels sur l'ecran, plutot des coordonnees
	// dans un plan 3D. La camera est placee par rapport aux matrices
	// de projection et translation.
	//
	// Les couleurs sont en format (rouge, vert, bleu)
	// Les coordonnees sont cartesiennes (x, y, z)
	glBegin(GL_TRIANGLES);
	//
	prog.setAttributeValue(ID_COLOR, 1.0, 0.0, 0.0);
	prog.setAttributeValue(ID_VERTEX, 0.0, 0.0, 0.0);
	//green
	prog.setAttributeValue(ID_COLOR, 0.0, 1.0, 0.0);
	prog.setAttributeValue(ID_VERTEX, 1.0, 0.0, 0.0);
	//blue
	prog.setAttributeValue(ID_COLOR, 0.0, 0.0, 1.0);
	prog.setAttributeValue(ID_VERTEX, 0.0, 1.0, 0.0);
	glEnd();
	// Fin de l'affichage du triangle.
}
