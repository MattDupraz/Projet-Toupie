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
