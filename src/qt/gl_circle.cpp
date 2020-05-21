#include "gl_circle.h"

#include "math.h"

void GLCircle::initialize(QOpenGLShaderProgram& prog) {
	QVector<Vertex> vertices;
	vertices.reserve(3 * sides);

	QVector3D e_y(0.0f,  1.0f, 0.0f);
	QVector3D O(0.0f, 0.0f, 0.0f);

	double d_theta(2 * M_PI / sides);
	for (unsigned int i(0); i < sides; ++i) {
		QVector3D v1(cos(d_theta * i), 0.0f, sin(d_theta * i));
		QVector3D v2(cos(d_theta * (i + 1)), 0.0f, sin(d_theta * (i + 1)));

		float red(0.5f - cos(d_theta * i) * 0.4f);
		float green(0.0f);
		float blue(0.5f + cos(d_theta * i) * 0.4f);
		QVector3D color(red, green, blue);
		
		vertices << Vertex {O , color, e_y }
			<< Vertex { v2, color, e_y }
			<< Vertex { v1, color, e_y };
	}

	create_vao(prog, vertices);	
}
