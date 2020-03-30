#include "view_text.h"
#include "systeme.h"
#include "integrator.h"
#include <iostream>
using namespace std;





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
	}
	
	cout << "reussi" << endl;
	return 0;
}
