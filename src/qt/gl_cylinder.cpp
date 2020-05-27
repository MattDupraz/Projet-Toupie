#include "gl_cylinder.h"

#include "math.h"

// Cylindre, deux bases (cercles) de rayon 1 à y = +- 1
void GLCylinder::initialize(QOpenGLShaderProgram& prog) {
	QVector<Vertex> vertices;
	vertices.reserve(6 * sides + 2 * 3 * sides);

	QVector3D y1(0.0f, -1.0f, 0.0f);
	QVector3D y2(0.0f,  1.0f, 0.0f);

	double d_theta(2 * M_PI / sides);
	for (unsigned int i(0); i < sides; ++i) {
		QVector3D v1(cos(d_theta * i), 0.0f, sin(d_theta * i));
		QVector3D v2(cos(d_theta * (i + 1)), 0.0f, sin(d_theta * (i + 1)));
		QVector3D normal(0.5f * (v1 + v2));

		float red(0.0f);
		float green(0.4f + cos(d_theta * i) * 0.4f);
		float blue(1.0f);
		QVector3D color(red, green, blue);
		
		vertices << Vertex { y1, color, y1 }
			<< Vertex { v1 + y1, color, y1 }
			<< Vertex { v2 + y1, color, y1 };
		vertices << Vertex { y2, color, y2 }
			<< Vertex { v2 + y2, color, y2 }
			<< Vertex { v1 + y2, color, y2 };
		vertices << Vertex { y1 + v1, color, normal }
			<< Vertex { y2 + v1, color, normal }
			<< Vertex { y2 + v2, color, normal };
		vertices << Vertex { y1 + v1, color, normal }
			<< Vertex { y2 + v2, color, normal }
			<< Vertex { y1 + v2, color, normal };
	}

	create_vao(prog, vertices);	
}
