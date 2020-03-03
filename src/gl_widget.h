#pragma once

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>

class GLWidget : public QOpenGLWidget {
	public:
		GLWidget(QWidget* parent = nullptr)
			:QOpenGLWidget(parent) {}
		virtual ~GLWidget() {}
	private:
		virtual void initializeGL() override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL() override;
		
		QOpenGLShaderProgram prog;
};
