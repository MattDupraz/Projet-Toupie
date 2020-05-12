#include "view_text.h"
#include "system.h"
#include "integrator.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

using namespace std;

int main(){
	constexpr double dt = 0.01;
	constexpr bool verbose = true;
	constexpr int nIterations = 1000;

	// Initialise le support de dessin
	shared_ptr<View> view = make_shared<ViewText>(verbose);
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
			Vector {0, 0, 1}, 
			Vector {0,0.5,0}, 
			Vector {0,0,70},
			0.1, 1.5, 0.75));	
	system.add(std::make_unique<ChineseTop>(view,
		Vector {0,0.5,0, 0, 0},
		Vector {0,0,170, 0, 0},
		0.1, 1.5, 0.2));
	system.add(make_unique<ToupiesGen>(view,
		Vector {0, 0, 2}, 
		Vector {0, 0.5, 0}, 
		Vector {0,0,70},
		0.1, Vector{0,0,2}, 1));
	

	// Affiche les conditions initialles du systeme
	cout << system;
	
	ofstream file1("./invariants/energie.txt");
	ofstream file2("./invariants/moment_cin_k.txt");
	ofstream file3("./invariants/moment_cin_a.txt");
	
	if (verbose) {
		cout << "Le système évolue et se dessine à chaque pas (dt = " << dt << "): "
			<< endl;
	} else {
		cout << "format: toupie\ttemps\tparamètre\tdérivée" << endl;
	}
	
	// Evolue le systeme nIterations fois
	for (int i(0); i < nIterations; ++i) {
		system.evolve(dt);
		system.draw();
		file1 << system.getTop(0).getEnergy() << std::endl;
		file2 << system.getTop(0).getL_Ak() << std::endl;
		file3 << system.getTop(0).getL_Aa() << std::endl;
		
	}	
	
	return 0;
}
