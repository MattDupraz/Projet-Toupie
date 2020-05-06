#include <QApplication>

#include "gl_widget.h"
#include "system.h"
#include "view_opengl.h"
#include "vect.h"
#include "math.h"

#include <memory>
#include <utility>
#include <iostream>

int main(int argc, char* argv[]) {
	// Initialise le support de dessin
	std::shared_ptr<ViewOpenGL> view = std::make_shared<ViewOpenGL>();
	// Initialise l'integrateur choisi
	std::shared_ptr<Integrator> integrator = std::make_shared<RungeKuttaIntegrator>();
	// Initialise le systeme
	std::unique_ptr<System> system = std::make_unique<System>(view, integrator);
	// Ajoute des toupies au systeme
	system->add(std::make_unique<Gyroscope>(view,
		Vector {-1, 0, -2},
		Vector {0, 0.5, 0},
		Vector {0, 0, 160},
		1.0, 0.1, 0.2, 1.0));
	system->add(std::make_unique<SimpleCone>(view,
		Vector {2, 0, 1},
		Vector {0,0.5,0},
		Vector {0,0,170},
		0.1, 1.5, 0.75));
	system->add(std::make_unique<ChineseTop>(view,
		Vector {0,0.5,0, 0, 0},
		Vector {0,0,15, 0, 0},
		0.1, 0.75, 0.6));
	
	// Affiche les conditions initialles du systeme
	std::cout << *system;
	
	// Initialise l'application Qt
	QApplication a(argc, argv);

	GLWidget w(std::move(system), view, 20);
	// Affiche la fenetre
	w.show();
	// Enclenche la boucle principale du programme
	return a.exec();
}
