#include "view_text.h"
#include "view_file.h"
#include "system.h"
#include "integrator_euler_cromer.h"
#include "integrator_newmark.h"
#include "integrator_runge_kutta.h"
#include "top_simple_cone.h"
#include "top_gyroscope.h"
#include "top_chinese.h"
#include "top_general.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

using namespace std;

int main(){
	constexpr double dt = 0.01;
	constexpr int nIterations = 2000;

	// Initialise le support de dessin
	shared_ptr<View> view = make_shared<ViewFile>();
	// Initialise l'integrateur choisi
	shared_ptr<Integrator> integrator = make_shared<NewmarkIntegrator>();
	// Initialise le systeme
	System system(view, integrator);
	// Ajoute des toupies au systeme
	system.add(make_unique<Gyroscope>(view, 
			Vector {0, 0, 0}, 
			Vector {0, 0.5, 0}, 
			Vector {0, 0, 160},
			1.0, 0.1, 0.2, 1.0));
	system.add(make_unique<SimpleCone>(view,
			Vector {0, 1, 0}, 
			Vector {0,0.523599,0}, 
			Vector {0,0,60},
			0.1, 1.5, 0.5));	
	system.add(std::make_unique<ChineseTop>(view,
		Vector {0,0.5,0, 0, 0},
		Vector {0,0,17, 0, 0},
		0.1, 1.5, 0.2));
	double rho = 0.1;
	double L = 1.5;
	double R = 0.75;
	int n_layers = 50;
	Vector layers;
	for (int i(0); i < n_layers; ++i) {
		layers.augment(R * ((double(i) + 0.5) / double(n_layers)));
	}

	system.add(std::make_unique<GeneralTop>(view,
		Vector {-3, 2, 0},
		Vector {0, 0.5, 0},
		Vector {0, 0, 170},
		rho, layers, L / double(n_layers)));

	// Affiche les conditions initialles du systeme
	cout << system;
	cout << "Le système évolue et se dessine à chaque pas (dt = " << dt << "): "
			<< endl;
	
	// Evolue le systeme nIterations fois
	for (int i(0); i < nIterations; ++i) {
		system.evolve(dt);
		system.draw();
<<<<<<< HEAD
		file1 << system.getTop(1).getAngMomentumA()*Vector {0,0,1} << std::endl;
		file2 << system.getTop(1).getAngMomentumG()*Vector {0,0,1} << std::endl;
		file3 << system.getTop(2).getEnergy() << std::endl;
		file4 << system.getTop(3).getEnergy() << std::endl;
=======
>>>>>>> f4bd8b1571b6fd7f24f5e3d4b2523e64cbebd953
	}	
	
	return 0;
}
