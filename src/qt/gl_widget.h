#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QEvent>

#include <memory>
#include <utility>

#include "view_opengl.h"
#include "top.h"
#include "integrator.h"
#include "system.h"

class GLWidget : public QOpenGLWidget {
	public:
		GLWidget(std::unique_ptr<System> system,
				std::shared_ptr<ViewOpenGL> view,
				int tickInterval);
		virtual ~GLWidget() {}
	private:
		virtual void initializeGL() override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL() override;
		virtual void timerEvent(QTimerEvent* event) override;
		virtual void keyPressEvent(QKeyEvent* event) override;
		virtual void keyReleaseEvent(QKeyEvent* event) override;
		virtual void mouseMoveEvent(QMouseEvent* event) override;
		virtual void mousePressEvent(QMouseEvent* event) override;
		virtual void enterEvent(QEvent* event) override;
		
		QPoint getWindowCenterPos();
		void setFocus(bool val);
		
		QElapsedTimer timer_;

		std::unique_ptr<System> system_;
		std::shared_ptr<ViewOpenGL> view_;
		
		int tickInterval_;

		bool focus_;

		double cameraYawSpeed_;
		double cameraPitchSpeed_;
		Vector cameraSpeed_;
		
		bool enableMouse_ = false;
		bool ignoreNextMouseMoveEvent_ = true;
};
