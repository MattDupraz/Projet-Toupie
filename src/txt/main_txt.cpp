#include "view_text.h"
#include "system.h"
#include "integrator.h"

#include <iostream>
#include <memory>
#include <utility>

using namespace std;

int main(){
	constexpr double dt = 0.01;
	constexpr bool verbose = true;

	shared_ptr<View> view = make_shared<ViewText>(verbose);
	shared_ptr<Integrator> integrator = make_shared<NewmarkIntegrator>();

	System system(view, integrator);
	system.add(make_unique<SimpleCone>(view, 
			Vector {0, 0, 0}, 
			Vector {0, 0.5, 0}, 
			Vector {0, 0, 60},
			0.1, 1.5, 0.5));
	system.add(make_unique<SimpleCone>(view,
			Vector {0, 0, 1}, 
			Vector {0,0.5,0}, 
			Vector {0,0,70},
			0.1, 1.5, 0.75));	


	cout << system;
	if (verbose) {
		cout << "Le système évolue et se dessine à chaque pas (dt = " << dt << "): "
			<< endl;
	} else {
		cout << "format: toupie\ttemps\tparamètre\tdérivée" << endl;
	}
	for (int i(0); i < 100; ++i) {
		system.evolve(dt);
		system.draw();
	}	
	
	return 0;
}
