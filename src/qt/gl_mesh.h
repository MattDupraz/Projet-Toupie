#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "vertex.h"

// GL Mesh est un objet 3D préparé pour l'affichage efficace en le
// envoyant directement au cache du GPU
class GLMesh
{
	public:
		// Le constructeur ne fait rien, l'objet doit être initialisé
		// à l'aide de la méthode initialize quand le shader program
		// est disponible
		GLMesh() {}
		virtual ~GLMesh() {}

		// Prépare l'objet et initialise le VAO
		virtual void initialize(QOpenGLShaderProgram& prog) = 0;

		// Déssine l'objet (doit être initialisé à priori)
		void draw();
	protected:
		// Initialise le VAO
		void create_vao(QOpenGLShaderProgram& prog,
				QVector<Vertex>& vertices);

		QOpenGLBuffer vbo;
		QOpenGLVertexArrayObject vao;
		unsigned int size = 0;
};
