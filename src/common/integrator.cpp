#include <iostream>
#include "integrator.h"

void EulerCromerIntegrator::evolve(
		Top& top, double dt){
	Vector P(top.getP());
	Vector DP(top.getDP());

	DP += dt*top.getDDP(P, DP);
	P += dt*DP;

	top.setP(P);
	top.setDP(DP);
}

void NewmarkIntegrator::evolve(
		Top& top, double dt){

}

void RungeKuttaIntegrator::evolve(
		Top& top, double dt){
	
}



