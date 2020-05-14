#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>

#include <map>
#include <vector>

#include "view.h"
#include "gl_mesh.h"
#include "gl_uniform.h"

class Top;
class Vector;

class ViewOpenGL : public View {
	public:
		ViewOpenGL()
			: shouldDrawFloor(true),
			shouldDrawTrajectories(true),
			cameraYaw(0.0),
			cameraPitch(-20.0),
			cameraPos(0.0, 0.4, 5.0),
			cameraFollow(false),
			followedTop(0)
			{}

		// Methodes pour dessiner des objets dessinables
		virtual void draw(SimpleCone const& top) override;
		virtual void draw(Gyroscope const& top) override;
		virtual void draw(ChineseTop const& top) override;
		virtual void draw(System const& system) override;

		// Ajoute une position a une trajectoire
		// La trajectoire est identifiee par un int unique
		void addToTrajectory(std::vector<QVector3D>&, QVector3D);
		// Dessine les trajectoires
		void drawTrajectory(std::vector<QVector3D> const&, QVector3D const& color);
		void drawTrajectories();
		// Dessine le sol
		void drawFloor();

		// Initialise le support de dessin au moment de la creation de la fenetre
		void init();
		// Emploi une matrice de projection
		void setProjection(QMatrix4x4 const& matrix);
		
		// Declenge/arrete le dessin du sol
		void triggerFloor() {shouldDrawFloor = !shouldDrawFloor;}
		// Declenge/arrete le dessin des trajectoires
		void triggerTrajectories() {shouldDrawTrajectories = !shouldDrawTrajectories;}
		// Enable following and follow next top
		void followNext();
		// Disable following
		void stopFollow();

		// Set object-dependent uniforms to their default value
		void resetUniforms();
		// Update the view uniform
		void updateView(System const& system);
		// Update the object-dependent uniforms
		void updateUniforms(Top const& top);

		// Tourne la camera (angle relatif)
		void rotateCamera(double yaw, double pitch);
		// Deplace la camera (position relative)
		void translateCamera(Vector diff);
	
	private:
		// Program lie aux shaders qu'on utilise
		QOpenGLShaderProgram prog;

		bool shouldDrawFloor;
		bool shouldDrawTrajectories;
		double cameraYaw;
		double cameraPitch;
		QVector3D cameraPos;

		bool cameraFollow; // true locks camera to followedTop
		int followedTop; // Index of followed top modulo number of tops

		// Valeurs uniformes
		UniformMatrix4x4 u_projection;
		UniformMatrix4x4 u_view;
		UniformMatrix4x4 u_translation;
		UniformMatrix4x4 u_model;

		// Dictionaire de trajectoires
		std::map<unsigned int, std::vector<QVector3D>> trajectoriesA;
		std::map<unsigned int, std::vector<QVector3D>> trajectoriesCM;

		// Nombre maximum de vecteurs dans une trajectoire
		int maxTrajectoryLength = 1000;

		// Meshes used for rendering
		GLMesh cone;
		GLMesh cylinder;
		GLMesh circle;
		GLMesh sphere;
};
