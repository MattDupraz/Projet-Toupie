#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>

#include <map>
#include <vector>

#include "view.h"
#include "gl_cone.h"
#include "gl_cylinder.h"
#include "gl_circle.h"
#include "gl_sphere.h"
#include "gl_uniform.h"

class Top;
class Vector;

// Classe qui s'occupe de l'affichage OpenGL
class ViewOpenGL : public View {
	public:
		ViewOpenGL();

		// Methodes pour dessiner des objets dessinables
		virtual void draw(SimpleCone const& top) override;
		virtual void draw(Gyroscope const& top) override;
		virtual void draw(ChineseTop const& top) override;
		virtual void draw(GeneralTop const& top) override;
		virtual void draw(System const& system) override;

		// Ajoute une position a une trajectoire
		// La trajectoire est identifiee par un int unique
		void addToTrajectory(std::vector<QVector3D>&, QVector3D);
		// Dessine les trajectoires
		void drawTrajectory(std::vector<QVector3D> const&, QVector3D const& color);
		void drawTrajectories();
		// Dessine le sol
		void drawFloor();

		// Dessine la base du systeme de coordonne x, y, z en rouge, vert, bleu
		void drawBasis();

		// Initialise le support de dessin au moment de la creation de la fenetre
		void init();
		// Emploi une matrice de projection
		void setProjection(QMatrix4x4 const& matrix);
		
		// Declenche/arrete le dessin du sol
		void triggerFloor() {shouldDrawFloor = !shouldDrawFloor;}
		// Declenche/arrete le dessin des trajectoires
		void triggerTrajectories() {shouldDrawTrajectories = !shouldDrawTrajectories;}
		// Declenche/arrete le dessin de la base de coordonnees
		void triggerBasis() {shouldDrawBasis = !shouldDrawBasis;}
		// Enable following and follow next top
		void followNext(bool rotate);
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
		bool shouldDrawBasis;
		double cameraYaw;
		double cameraPitch;
		QVector3D cameraPos;

		bool cameraFollow; // true locks camera to followedTop
		bool cameraRotateWithTop; // true puts camera into the top's reference frame
		int followedTop; // Index of followed top modulo number of tops

		// Meshes used for rendering
		GLCone cone;
		GLCylinder cylinder;
		GLCircle circle;
		GLSphere sphere;

		// Valeurs uniformes
		UniformMatrix4x4 u_projection;
		UniformMatrix4x4 u_view;
		UniformMatrix4x4 u_translation;
		UniformMatrix4x4 u_model;
		UniformFloat u_clipMaxY;
		UniformFloat u_clipMinY;
		UniformVector3D u_lightPos;
		UniformVector3D u_lightColor;
		UniformVector3D u_viewPos;

		// Dictionaire de trajectoires
		std::map<unsigned int, std::vector<QVector3D>> trajectoriesA;
		std::map<unsigned int, std::vector<QVector3D>> trajectoriesCM;

		// Nombre maximum de vecteurs dans une trajectoire
		int maxTrajectoryLength = 1000;
};
