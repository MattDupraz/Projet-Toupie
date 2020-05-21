#pragma once

#include "gl_mesh.h"

// Cylinder
// Two bases of radius 1 at y = 1, -1
class GLCylinder : public GLMesh {
	public:
		GLCylinder(unsigned int sides)
			:sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int sides;
};
