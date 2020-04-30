#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "vertex.h"

class GLMesh
{
	public:
		GLMesh() {}
		virtual ~GLMesh() {}

		void init(QOpenGLShaderProgram& prog,
				QVector<Vertex>& vertices);
		void init_cone(QOpenGLShaderProgram& prog,
				unsigned int slices);
		void init_disk(QOpenGLShaderProgram& prog,
				unsigned int slices);
		void draw();
	protected:
		QOpenGLBuffer vbo;
		QOpenGLVertexArrayObject vao;
		unsigned int size = 0;
};
