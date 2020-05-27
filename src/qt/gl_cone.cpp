#include "gl_cone.h"

#include "math.h"

// Cône avec sommet en 0, de hauteur 1 (dans la direction y)
// et diamètre de base 1
void GLCone::initialize(QOpenGLShaderProgram& prog) {
	QVector<Vertex> vertices;
	vertices.reserve(6 * sides);

	QVector3D origin(0.0f, 0.0f, 0.0f);
	QVector3D e_y(0.0f, 1.0f, 0.0f);

	double d_theta(2 * M_PI / sides);
	for (unsigned int i(0); i < sides; ++i) {
		QVector3D v1(cos(d_theta * i), 1.0f, sin(d_theta * i));
		QVector3D v2(cos(d_theta * (i + 1)), 1.0f, sin(d_theta * (i + 1)));
		QVector3D normal(QVector3D::crossProduct(v1, v2).normalized());

		float red(1.0f);
		float green(0.4f + cos(d_theta * i) * 0.4f);
		float blue(0.0f);
		QVector3D color(red, green, blue);
		
		vertices << Vertex { origin, color, normal }
			<< Vertex { v1, color, normal }
			<< Vertex { v2, color, normal };
		vertices << Vertex { e_y, color, e_y }
			<< Vertex { v2, color, e_y }
			<< Vertex { v1, color, e_y };
	}

	create_vao(prog, vertices);
}
