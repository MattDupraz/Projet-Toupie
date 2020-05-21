#pragma once

#include "gl_mesh.h"

// Cone
// Pointy part at origin
// Base of radius 1 at y = 1
class GLCone : public GLMesh {
	public:
		GLCone(unsigned int sides)
			:sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int sides;
};
