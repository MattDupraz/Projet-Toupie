#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <QTimerEvent>

#include "view_opengl.h"
#include "top.h"
#include "integrator.h"

#include "math.h"

class GLWidget : public QOpenGLWidget {
	public:
		GLWidget(QWidget* parent = nullptr)
			:QOpenGLWidget(parent),
			simpleCone_( &view_,
					Vector {0, M_PI / 6.0, 0},
					Vector {0, 0, 160.0},
					0.1,
					1.5,
					0.5)
	  	{}
		virtual ~GLWidget() {}
	private:
		virtual void initializeGL() override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL() override;
		virtual void timerEvent(QTimerEvent* event) override;
		
		ViewOpenGL view_;

		SimpleCone simpleCone_;
		NewmarkIntegrator integrator_;

		QElapsedTimer timer_;
};
