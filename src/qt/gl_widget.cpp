#include <QMatrix4x4>
#include "gl_widget.h"
#include "vertex_shader.h"

// Appelee une fois au debut du programme
void GLWidget::initializeGL() {
	view_.init();
	
	startTimer(10);
	timer_.restart();
}

void GLWidget::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);

	double dt = timer_.restart() / 1000.0;
	integrator_.evolve(simpleCone_, dt);
	view_.rotateCamera(cameraYawSpeed_ * dt,
			cameraPitchSpeed_ * dt);
	view_.translateCamera(cameraSpeed_ * dt);

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
	view_.setProjection(projectionMatrix);
}

// Appellee a chaque frame
void GLWidget::paintGL() {
	// Reinitialise le buffer de couleur et de profondeur
	// Necessaire pour ne pas avoir de surprises
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view_.setupScene();
	simpleCone_.draw();
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
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
			view_.triggerFloor();
			break;
	}
}

void GLWidget::keyReleaseEvent(QKeyEvent* event) {
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
