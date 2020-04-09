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
		// le tickInterval est la duree en millisecondes d'un pas de temps
		// Une valeur trop haute peux mener a un comportement instable
		GLWidget(std::unique_ptr<System> system,
				std::shared_ptr<ViewOpenGL> view,
				int tickInterval);
		virtual ~GLWidget() {}
	private:
		// Toutes les methodes override suivantes sont appelle par OpenGL!
		// Initialise l'environment graphique
		virtual void initializeGL() override;
		// Methode qui gere les changements de taille de la fenetre
		virtual void resizeGL(int width, int height) override;
		// Dessin de la fenetre
		virtual void paintGL() override;
		// Methode appelee quand une fois le pas de temps ecoule
		virtual void timerEvent(QTimerEvent* event) override;
		// Methode appelee quand une touche est apuyee
		virtual void keyPressEvent(QKeyEvent* event) override;
		// Methode appelee quand une touche est relachee
		virtual void keyReleaseEvent(QKeyEvent* event) override;
		// Methode appelee quand la souris est bougee
		virtual void mouseMoveEvent(QMouseEvent* event) override;
		// Methode appelee quand une touche de la souris est apuyee
		virtual void mousePressEvent(QMouseEvent* event) override;
		// Methode appelee quand la souris rentre dans la fenetre
		virtual void enterEvent(QEvent* event) override;
		
		// Methode qui renvoie le milieu de la fenetre
		QPoint getWindowCenterPos();
		// Methode qui gere le focus - pour bloquer la souris dans la fenetre
		void setFocus(bool val);
		
		// Timer qui gere le temps pour la simulation
		QElapsedTimer timer_;

		// Systeme contenant les toupies
		std::unique_ptr<System> system_;
		// Classe qui gere l'affichage des toupies
		std::shared_ptr<ViewOpenGL> view_;
		
		// Pas de temps
		int tickInterval_;
		// Attribut qui permet de sortir la souris de la fenetre
		bool focus_;

		// Vitesse de rotation horizontalle de la camera
		double cameraYawSpeed_;
		// Vitesse de rotation verticalle de la camera
		double cameraPitchSpeed_;
		// Vitesse de translation de la camera
		Vector cameraSpeed_;
		
		// Attribut qui autorise l'utilisation de la souris
		// Attention!!! la souris ne marche pas bien dans les machines virtuelles!
		bool enableMouse_ = false;
		// Attribut qui permet d'ignorer la souris (une iteration)
		bool ignoreNextMouseMoveEvent_ = true;
};
