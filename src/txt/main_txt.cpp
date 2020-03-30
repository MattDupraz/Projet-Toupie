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
	system.add(make_unique<Gyroscope>(view, 
			Vector {0, 0, 0}, 
			Vector {0, 0.5, 0}, 
			Vector {0, 0, 60},
			1.0, 0.1, 0.2, 1.0));
	system.add(make_unique<SimpleCone>(view,
			Vector {0, 0, 1}, 
			Vector {0,0.5,0}, 
			Vector {0,0,70},
			0.1, 1.5, 0.75));	


<<<<<<< HEAD
int main(){
	// Déclaration des objets nécessaires
	ViewText objetbizarre;
	SimpleCone top(&objetbizarre, {0,0.5,0},{0,0,60},0.1,1.5,0.5);
	SimpleCone top2(&objetbizarre, {0,0.5,0},{0,0,70},0.1,1.5,0.75);
	NewmarkIntegrator in;
	
	// Création du système
	System syst(&objetbizarre, &top, &in);
	syst.add(&top2);
	// Affiche le système
	syst.draw();
	// L'évolution du systèmegit 
	for (int i(0); i<100 ; ++i){
		std::cout << i*0.2 << std::endl;
		syst.evolve(0.2);
=======
	cout << system;
	if (verbose) {
		cout << "Le système évolue et se dessine à chaque pas (dt = " << dt << "): "
			<< endl;
	} else {
		cout << "format: toupie\ttemps\tparamètre\tdérivée" << endl;
>>>>>>> a94d5784f707962d0ff05b9458f71e307f7ea6bf
	}
	for (int i(0); i < 100; ++i) {
		system.evolve(dt);
		system.draw();
	}	
	
	return 0;
}
