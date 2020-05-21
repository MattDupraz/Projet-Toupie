#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "vertex.h"

// GL Mesh Represents a drawable object pre-buffered into the GPU
class GLMesh
{
	public:
		// Constructor doesn't actually do anything
		// To initialize the mesh, refer to the functions below
		GLMesh() {}
		virtual ~GLMesh() {}

		virtual void initialize(QOpenGLShaderProgram& prog) = 0;

		// Draw the mesh (needs to be initialized first)
		void draw();
	protected:
		// initialize vao
		void create_vao(QOpenGLShaderProgram& prog,
				QVector<Vertex>& vertices);

		QOpenGLBuffer vbo;
		QOpenGLVertexArrayObject vao;
		unsigned int size = 0;
};
