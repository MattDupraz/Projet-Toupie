#pragma once

#include "gl_mesh.h"

// Cercle centré en 0, de rayon 1, dans le plan x-z
class GLCircle : public GLMesh {
	public:
		GLCircle(unsigned int sides)
			:sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int sides;
};
