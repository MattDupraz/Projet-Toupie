#pragma once

#include "gl_mesh.h"

// Cône avec sommet en 0, de hauteur 1 (dans la direction y)
// et diamètre de base 1
class GLCone : public GLMesh {
	public:
		GLCone(unsigned int sides)
			:sides(sides)
		{}

		void initialize(QOpenGLShaderProgram& prog);

	private:
		unsigned int sides;
};
