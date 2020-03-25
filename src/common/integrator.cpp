#include <iostream>
#include "integrator.h"
#include "math.h"

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
	Vector oldP(top.getP());
	Vector oldDP(top.getDP());
	Vector P(oldP);
	Vector DP(oldDP);

	Vector s(top.getDDP(P, DP));
	Vector q(P);
	do{
		q = P;
		Vector r(top.getDDP(P, DP));
		
		DP = oldDP + dt/2.0 * (r + s);
		P = oldP + dt*oldDP + pow(dt, 2)/3.0 * (1.0/2.0 * r + s);
	} while ((P - q).norm() >= epsilon);
	top.setP(P);
	top.setDP(DP);
}

void RungeKuttaIntegrator::evolve(
		Top& top, double dt){
	
}



