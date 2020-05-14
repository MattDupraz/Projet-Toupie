#include "integrator_euler_cromer.h"
#include "math.h"

// Implementation de la methode d'Euler
void EulerCromerIntegrator::evolve(
		Top& top, double dt){
	Vector P(top.getP());
	Vector DP(top.getDP());

	DP += dt*top.getDDP(P, DP);
	P += dt*DP;

	top.setP(P);
	top.setDP(DP);
}

