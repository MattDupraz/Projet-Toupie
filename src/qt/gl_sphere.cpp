#include "gl_sphere.h"

#include "math.h"

void GLSphere::initialize(QOpenGLShaderProgram& prog) {
	QVector<Vertex> vertices;
	vertices.reserve(6 * sides * slices - 2 * 3 * sides);

	QVector3D e_y(0.0f, 1.0f, 0.0f);

	double d_theta(2 * M_PI / sides);
	double d_phi(M_PI / slices);
	for (unsigned int i(0); i < slices; ++i) {
		double phi1 = i * d_phi;
		double phi2 = (i + 1) * d_phi;
		double r1 = sin(phi1);
		double r2 = sin(phi2);
		double y1 = cos(phi1);
		double y2 = cos(phi2);
		for (unsigned int j(0); j < sides; ++j) {
			double theta1 = j * d_theta;
			double theta2 = (j + 1) * d_theta;
			double x1 = cos(theta1);
			double x2 = cos(theta2);
			double z1 = sin(theta1);
			double z2 = sin(theta2);

			QVector3D v11(r1*x1, y1, r1*z1);
			QVector3D v12(r1*x2, y1, r1*z2);
			QVector3D v21(r2*x1, y2, r2*z1);
			QVector3D v22(r2*x2, y2, r2*z2);

			QVector3D normal1((1.0f/3.0f) * (v11 + v12 + v22));
			QVector3D normal2((1.0f/3.0f) * (v11 + v21 + v22));

			float red(0.5f - cos(theta1) * 0.4f);
			float green(0.0f);
			float blue(0.5f + cos(theta1) * 0.4f);
			QVector3D color(red, green, blue);
			
			if (v11 != v12) {
				vertices << Vertex { v11, color, normal1 }
					<< Vertex { v12, color, normal1 }
					<< Vertex { v22, color, normal1 };
			}
			if (v21 != v22) {
				vertices << Vertex { v11, color, normal2 }
					<< Vertex { v22, color, normal2 }
					<< Vertex { v21, color, normal2 };
			}
		}
	}

	create_vao(prog, vertices);	
}
