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
				unsigned int sides);
		void init_cylinder(QOpenGLShaderProgram& prog,
				unsigned int sides);
		void init_circle(QOpenGLShaderProgram& prog,
				unsigned int sides);
		void init_sphere(QOpenGLShaderProgram& prog,
				unsigned int slices, unsigned int sides);
		void draw();
	protected:
		QOpenGLBuffer vbo;
		QOpenGLVertexArrayObject vao;
		unsigned int size = 0;
};
