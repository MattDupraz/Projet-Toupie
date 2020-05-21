#pragma once

#include "gl_mesh.h"

// Circle centered around origin, radius 1
class GLCircle : public GLMesh {
	public:
		GLCircle(unsigned int sides)
			:sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int sides;
};
