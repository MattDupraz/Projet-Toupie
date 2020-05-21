#include <QOpenGLFunctions>
#include "gl_mesh.h"
#include "vertex_shader.h"

void GLMesh::create_vao(QOpenGLShaderProgram& prog,
		QVector<Vertex>& vertices) {
	// Create the Vertex Buffer Object from the set of vertices
	vbo.create();
	vbo.bind();
	vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo.allocate(vertices.constData(), vertices.size() * sizeof(Vertex));

	// Create the Vertex Array Object
	vao.create();
	vao.bind();

	// Define how the VBO is used when the VAO is bound
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
