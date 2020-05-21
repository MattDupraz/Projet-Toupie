#pragma once

#include "gl_mesh.h"

// Sphere
// Centered around origin, radius 1
class GLSphere : public GLMesh {
	public:
		GLSphere(unsigned int slices, unsigned int sides)
			:slices(slices), sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int slices;
		unsigned int sides;
};
