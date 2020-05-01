#include <QOpenGLFunctions>
#include "gl_mesh.h"
#include "vertex_shader.h"
#include "math.h"

void GLMesh::init(QOpenGLShaderProgram& prog,
		QVector<Vertex>& vertices) {
	vbo.create();
	vbo.bind();
	vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo.allocate(vertices.constData(), vertices.size() * sizeof(Vertex));

	vao.create();
	vao.bind();

	prog.enableAttributeArray(aPos);	
	prog.enableAttributeArray(aColor);
	prog.enableAttributeArray(aNormal);
	prog.setAttributeBuffer(aPos, GL_FLOAT, Vertex::posOffset(), 3, Vertex::stride());
	prog.setAttributeBuffer(aColor, GL_FLOAT, Vertex::colorOffset(), 3, Vertex::stride());
	prog.setAttributeBuffer(aNormal, GL_FLOAT, Vertex::normalOffset(), 3, Vertex::stride());

	vao.release();
	vbo.release();

	size = vertices.size();
}

void GLMesh::draw() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, size);
	vao.release();
}

void GLMesh::init_cone(QOpenGLShaderProgram& prog, unsigned int sides) {
	QVector<Vertex> vertices;
	vertices.reserve(6 * sides);

	QVector3D origin(0.0f, 0.0f, 0.0f);
	QVector3D e_z(0.0f, 1.0f, 0.0f);

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
		vertices << Vertex { e_z, color, e_z }
			<< Vertex { v2, color, e_z }
			<< Vertex { v1, color, e_z };
	}

	init(prog, vertices);
}

void GLMesh::init_disk(QOpenGLShaderProgram& prog, unsigned int sides) {
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

	init(prog, vertices);	
}

void GLMesh::init_sphere(QOpenGLShaderProgram& prog,
		unsigned int slices, unsigned int sides) {
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

	init(prog, vertices);	
}
