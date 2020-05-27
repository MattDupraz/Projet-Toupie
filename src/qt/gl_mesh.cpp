#include <QOpenGLFunctions>
#include "gl_mesh.h"
#include "vertex_shader.h"

// Crée le VAO qu'on peut en suite utiliser pour dessiner l'objet
void GLMesh::create_vao(QOpenGLShaderProgram& prog,
		QVector<Vertex>& vertices) {
	// Crée le VBO avec la liste des `Vertex`
	vbo.create();
	vbo.bind();
	vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo.allocate(vertices.constData(), vertices.size() * sizeof(Vertex));

	// Crée le VAO
	vao.create();
	vao.bind();

	// Définie l'utilisation du VBO lors du bind du VAO
	prog.enableAttributeArray(aPos);	
	prog.enableAttributeArray(aColor);
	prog.enableAttributeArray(aNormal);
	prog.setAttributeBuffer(aPos, GL_FLOAT, Vertex::posOffset(), 3, Vertex::stride());
	prog.setAttributeBuffer(aColor, GL_FLOAT, Vertex::colorOffset(), 3, Vertex::stride());
	prog.setAttributeBuffer(aNormal, GL_FLOAT, Vertex::normalOffset(), 3, Vertex::stride());

	// Relâche le VAO et VBO
	vao.release();
	vbo.release();

	size = vertices.size();
}

// Dessine l'objet
void GLMesh::draw() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, size);
	vao.release();
}
