#pragma once

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "view.h"
#include "top.h"

class ViewOpenGL : public View {
	public:
		ViewOpenGL()
			: drawFloor(true),
			cameraYaw(0.0),
			cameraPitch(-20.0),
			cameraPos({ 0.0, 0.4, 5.0 })
			{}

		virtual void draw(SimpleCone const& top) override;
		void init();
		void setupScene();
		void setProjection(QMatrix4x4 const& projection) {
			prog.setUniformValue("projection", projection);
		}
		
		void triggerFloor() {drawFloor = !drawFloor;}

		void rotateCamera(double yaw, double pitch);
		void translateCamera(Vector diff);
	
	private:
		QOpenGLShaderProgram prog;
		
		bool drawFloor;
		double cameraYaw;
		double cameraPitch;
		Vector cameraPos;
};
