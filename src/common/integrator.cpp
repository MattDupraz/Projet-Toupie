#include <iostream>
#include "integrator.h"

void EulerCromerIntegrator::evolve(
		Top& top, double dt){
	top.setDP(top.getDP() + dt*top.getDDP());
	top.setP(top.getP() + dt*top.getDP());
}

void NewmarkIntegrator::evolve(
		Top& top, double dt){

}

void RungeKuttaIntegrator::evolve(
		Top& top, double dt){

	
}



