#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>

#include <map>
#include <vector>

#include "view.h"
#include "top.h"

class ViewOpenGL : public View {
	public:
		ViewOpenGL()
			: shouldDrawFloor(true),
			shouldDrawTrajectories(true),
			cameraYaw(0.0),
			cameraPitch(-20.0),
			cameraPos({ 0.0, 0.4, 5.0 })
			{}

		virtual void draw(SimpleCone const& top) override;
		virtual void draw(Gyroscope const& top) override;
		virtual void draw(System const& system) override;

		void addToTrajectory(unsigned int, QVector3D);
		void drawTrajectories();
		void drawFloor();

		void init();
		void setProjection(QMatrix4x4 const& projection) {
			prog.setUniformValue("projection", projection);
		}
		
		void triggerFloor() {shouldDrawFloor = !shouldDrawFloor;}
		void triggerTrajectories() {shouldDrawTrajectories = !shouldDrawTrajectories;}

		void rotateCamera(double yaw, double pitch);
		void translateCamera(Vector diff);
	
	private:
		QOpenGLShaderProgram prog;
		
		bool shouldDrawFloor;
		bool shouldDrawTrajectories;
		double cameraYaw;
		double cameraPitch;
		Vector cameraPos;

		std::map<unsigned int, std::vector<QVector3D>> trajectories;

		int maxTrajectoryLength = 1000;
};
