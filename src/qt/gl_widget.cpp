#include <QMatrix4x4>
#include "gl_widget.h"
#include "vertex_shader.h"
#include "math.h"

#include <QPoint>
#include <QCursor>


GLWidget::GLWidget(std::unique_ptr<System> system,
		std::shared_ptr<ViewOpenGL> view,
		int tickInterval)
	:QOpenGLWidget(nullptr),
	system_(std::move(system)),
	view_(std::move(view)),
	tickInterval_(tickInterval),
	focus_(true),
	cameraYawSpeed_(0.0),
	cameraPitchSpeed_(0.0),
	cameraSpeed_({0.0, 0.0, 0.0})
{}  


// Appelee une fois au debut du programme
void GLWidget::initializeGL() {
	view_->init();
	
	startTimer(tickInterval_);
	timer_.restart();
}

void GLWidget::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);
	
	constexpr double throttleFactor(1.2);

	double dt = timer_.restart() / 1000.0;
	dt = std::min(dt, throttleFactor * (tickInterval_ / 1000.0));

	system_->evolve(dt);
	view_->rotateCamera(cameraYawSpeed_ * dt,
			cameraPitchSpeed_ * dt);
	view_->translateCamera(cameraSpeed_ * dt);

	update();
}

// Appellee a chaque fois que la taille de la fenetre change
void GLWidget::resizeGL(int width, int height) {
	// Definit la partie de la fenetre pour dessiner
	glViewport(0, 0, width, height);

	// Matrice de projection cree la perspective dans l'affichage
	// (voir /res/vertex_shader.glsl)
	QMatrix4x4 projectionMatrix;

	// QMatrix4x4::perspective(float verticalAngle, float aspectRation,
	// 						float nearPlane, float farPlane)
	// Cree la matrice de projection.
	projectionMatrix.perspective(70.0,
			width/(height ? height : 1.0), 1e-3, 1e5);

	// Assigne la matrice de projection a la valeur uniforme pour
	// l'utiliser dans le shader
	view_->setProjection(projectionMatrix);
}

// Appellee a chaque frame
void GLWidget::paintGL() {
	// Reinitialise le buffer de couleur et de profondeur
	// Necessaire pour ne pas avoir de surprises
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	system_->draw();
}

QPoint GLWidget::getWindowCenterPos() {
	QRect windowRect(contentsRect());
	QPoint windowCenter(QWidget::mapToGlobal(
				windowRect.topLeft()
				+ (windowRect.bottomRight() - windowRect.topLeft())/2.0));
	return windowCenter;
}

void GLWidget::setFocus(bool val) {
	if (!enableMouse_) return;
	
	focus_ = val;
	if (focus_) {
		ignoreNextMouseMoveEvent_ = true;
		QCursor::setPos(getWindowCenterPos());
		setCursor(Qt::BlankCursor);
		setMouseTracking(true);
	} else {
		setMouseTracking(false);
		setCursor(Qt::ArrowCursor);
	}
}	

void GLWidget::enterEvent(QEvent* event) {
	if (!enableMouse_) return;

	Q_UNUSED(event);
	// This prevents unintended behaviour when focus is lost
	// without the focus_ being triggered - e.g. when alt tabbing
	// and when the application first starts up
	if (focus_) {
		setFocus(true);
	}
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
	if (enableMouse_ && focus_ && !ignoreNextMouseMoveEvent_) {	
		QPoint windowCenter(getWindowCenterPos());
		QPoint diff(event->globalPos() - windowCenter);

		constexpr double sensitivity(0.3);
		view_->rotateCamera(-diff.x() * sensitivity, -diff.y() * sensitivity);

		QCursor::setPos(windowCenter);
	}

	ignoreNextMouseMoveEvent_ = false;
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
	Q_UNUSED(event);
	if(enableMouse_ && !focus_) {
		setFocus(true);
	}
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
	if (focus_ || !enableMouse_) {
		constexpr double dAngle(80.0);
		constexpr double dPos(5.0);
		switch(event->key()) {
			case Qt::Key_Left:
				cameraYawSpeed_ += dAngle;
				break; 
			case Qt::Key_Right:
				cameraYawSpeed_ -= dAngle;
				break;
			case Qt::Key_Up:
				cameraPitchSpeed_ += dAngle;
				break;
			case Qt::Key_Down:
				cameraPitchSpeed_ -= dAngle;
				break;
			case Qt::Key_W:
				cameraSpeed_ += Vector{0.0, 0.0, -dPos};
				break;
			case Qt::Key_S:
				cameraSpeed_ += Vector{0.0, 0.0, dPos};
				break;
			case Qt::Key_A:
				cameraSpeed_ += Vector{-dPos, 0.0, 0.0};
				break;
			case Qt::Key_D:
				cameraSpeed_ += Vector{dPos, 0.0, 0.0};
				break;
			case Qt::Key_Shift:
				cameraSpeed_ += Vector{0.0, -dPos, 0.0};
				break;
			case Qt::Key_Space:
				cameraSpeed_ += Vector{0.0, dPos, 0.0};
				break;
			case Qt::Key_F:
				view_->triggerFloor();
				break;
			case Qt::Key_T:
				view_->triggerTrajectories();
				break;
			case Qt::Key_Escape:
				cameraSpeed_ = Vector {0, 0, 0};
				cameraPitchSpeed_ = 0;
				cameraYawSpeed_ = 0;
				setFocus(false);
				break;
		}
	}
}

void GLWidget::keyReleaseEvent(QKeyEvent* event) {
	if (focus_ || !enableMouse_) {
		constexpr double dAngle(80.0);
		constexpr double dPos(5.0);
		switch(event->key()) {
			case Qt::Key_Left:
				cameraYawSpeed_ -= dAngle;
				break; 
			case Qt::Key_Right:
				cameraYawSpeed_ += dAngle;
				break;
			case Qt::Key_Up:
				cameraPitchSpeed_ -= dAngle;
				break;
			case Qt::Key_Down:
				cameraPitchSpeed_ += dAngle;
				break;
			case Qt::Key_W:
				cameraSpeed_ += Vector{0.0, 0.0, dPos};
				break;
			case Qt::Key_S:
				cameraSpeed_ += Vector{0.0, 0.0, -dPos};
				break;
			case Qt::Key_A:
				cameraSpeed_ += Vector{dPos, 0.0, 0.0};
				break;
			case Qt::Key_D:
				cameraSpeed_ += Vector{-dPos, 0.0, 0.0};
				break;
			case Qt::Key_Shift:
				cameraSpeed_ += Vector{0.0, dPos, 0.0};
				break;
			case Qt::Key_Space:
				cameraSpeed_ += Vector{0.0, -dPos, 0.0};
				break;
		}
	}
}
