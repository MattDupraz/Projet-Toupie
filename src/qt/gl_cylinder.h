#pragma once

#include "gl_mesh.h"

// Cylindre, deux bases (cercles) de rayon 1 à y = +- 1
class GLCylinder : public GLMesh {
	public:
		GLCylinder(unsigned int sides)
			:sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int sides;
};
