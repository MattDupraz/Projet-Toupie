#pragma once

#include "gl_mesh.h"

// Sphère centrée en 0 de rayon 1
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
