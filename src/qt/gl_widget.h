#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>

#include "view_opengl.h"
#include "top.h"

class GLWidget : public QOpenGLWidget {
	public:
		GLWidget(QWidget* parent = nullptr)
			:QOpenGLWidget(parent), top_(&view_) {}
		virtual ~GLWidget() {}
	private:
		virtual void initializeGL() override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL() override;
		virtual void timerEvent(QTimerEvent* event) override;
		
		ViewOpenGL view_;
		Top top_;

		QElapsedTimer timer_;
};
