#include "integrator_newmark.h"
#include "math.h"

// Implementation de la methode de Newmark
void NewmarkIntegrator::evolve(
		Top& top, double dt){
	
	Vector oldP(top.getP());
	Vector oldDP(top.getDP());
	Vector P(oldP);
	Vector DP(oldDP);

	Vector s(top.getDDP(P, DP));
	Vector q(P);
	
	// Variable count introduite pour empecher une boucle infinie
	int count(0);
	
	do{
		q = P;
		Vector r(top.getDDP(P, DP));
		
		DP = oldDP + dt/2.0 * (r + s);
		P = oldP + dt*oldDP + pow(dt, 2)/3.0 * (1.0/2.0 * r + s);
		++count;
		
	} while ((P - q).norm() >= epsilon && count < 1000);
	top.setP(P);
	top.setDP(DP);
}
