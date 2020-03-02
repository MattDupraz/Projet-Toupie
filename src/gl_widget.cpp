#include <QMatrix4x4>
#include "gl_widget.h"
#include "vertex_shader.h"

void GLWidget::initializeGL() {
	prog.addShaderFromSourceFile(QOpenGLShader::Vertex,
			":/vertex_shader.glsl");
	prog.addShaderFromSourceFile(QOpenGLShader::Fragment,
			":/fragment_shader.glsl");
	prog.bindAttributeLocation("vertex", ID_VERTEX);
	prog.bindAttributeLocation("color", ID_COLOR);
	prog.link();
	prog.bind();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	QMatrix4x4 projection_matrix;
	projection_matrix.perspective(70.0,
			qreal(width)/qreal(height ? height : 1.0), 1e-3, 1e5);
	prog.setUniformValue("projection", projection_matrix);
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	QMatrix4x4 viewport_matrix;
	viewport_matrix.translate(0.0, 0.0, -2.0);
	prog.setUniformValue("viewport", viewport_matrix);

	glBegin(GL_TRIANGLES);
	//red
	prog.setAttributeValue(ID_COLOR, 1.0, 0.0, 0.0);
	prog.setAttributeValue(ID_VERTEX, 0.0, 0.0, 0.0);
	//green
	prog.setAttributeValue(ID_COLOR, 0.0, 1.0, 0.0);
	prog.setAttributeValue(ID_VERTEX, 1.0, 0.0, 0.0);
	//blue
	prog.setAttributeValue(ID_COLOR, 0.0, 0.0, 1.0);
	prog.setAttributeValue(ID_VERTEX, 0.0, 1.0, 0.0);
	glEnd();
}
