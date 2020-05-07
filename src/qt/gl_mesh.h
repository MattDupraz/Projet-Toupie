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

		// Initialize an arbitrary mesh
		void init(QOpenGLShaderProgram& prog,
				QVector<Vertex>& vertices);
		// Initialize a cone mesh
		// Pointy part at origin, base of radius 1 at y = 1
		void init_cone(QOpenGLShaderProgram& prog,
				unsigned int sides);
		// Initialize a cylinder mesh
		// Two bases of radius 1 at y = 1, -1
		void init_cylinder(QOpenGLShaderProgram& prog,
				unsigned int sides);
		// Initialize a circle mesh
		// Centered around origin, radius 1
		void init_circle(QOpenGLShaderProgram& prog,
				unsigned int sides);
		// Initialize a sphere mesh
		// Centered around origin, radius 1
		void init_sphere(QOpenGLShaderProgram& prog,
				unsigned int slices, unsigned int sides);

		// Draw the mesh (needs to be initialized first)
		void draw();
	protected:
		QOpenGLBuffer vbo;
		QOpenGLVertexArrayObject vao;
		unsigned int size = 0;
};
