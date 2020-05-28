#include <QApplication>

#include "gl_widget.h"
#include "system.h"
#include "integrator.h"
#include "integrator_runge_kutta.h"
#include "integrator_newmark.h"
#include "integrator_euler_cromer.h"
#include "top.h"
#include "top_gyroscope.h"
#include "top_simple_cone.h"
#include "top_chinese.h"
#include "top_general.h"
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
		Vector {-1, -2, 0},
		Vector {0, 0.5, 0},
		Vector {0, 0, 5},
		1.0, 0.1, 0.2, 1.0));

	// On prépare la toupie générale t.q. elle approxime la toupie conique
	// aussi près que possible
	double rho = 0.1;
	double L = 1.5;
	double R = 0.75;
	int n_layers = 100;
	Vector layers;
	for (int i(0); i < n_layers; ++i) {
		layers.augment(R * abs(sin(M_PI*pow((double(i) + 0.5) / double(n_layers), 2.0))));
	}
	system->add(std::make_unique<GeneralTop>(view,
		Vector {0, 0.5, 0, 0, 0},
		Vector {0, 0, 170, -3, 2},
		rho, layers, L / double(n_layers)));
	
	system->add(std::make_unique<SimpleCone>(view,
		Vector {2, 1, 0},
		Vector {0,0.5,0},
		Vector {0,0,170},
		rho, L, R));


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
