#include <iostream>
#include "integrator.h"
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

// Implementation de la methode Runge-Kutta
void RungeKuttaIntegrator::evolve(
		Top& top, double dt){
	Vector P(top.getP());
	Vector DP(top.getDP());

	Vector DP_1 = DP;
	Vector DDP_1 = top.getDDP(P, DP);
	
	Vector DP_2 = DP + dt/2.0 * DDP_1;
	Vector DDP_2 = top.getDDP(P + dt/2.0 * DP_1, DP + dt/2.0 * DDP_1);

	Vector DP_3 = DP + dt/2.0 * DDP_2;
	Vector DDP_3 = top.getDDP(P + dt/2.0 * DP_2, DP + dt/2.0 * DDP_2);

	Vector DP_4 = DP + dt * DDP_3;
	Vector DDP_4 = top.getDDP(P + dt * DP_3, DP + dt * DDP_3);

	Vector weightedDP = 1.0/6.0 * (DP_1 + 2.0*DP_2 + 2.0*DP_3 + DP_4);
	Vector weightedDDP = 1.0/6.0 * (DDP_1 + 2.0*DDP_2 + 2.0*DDP_3 + DDP_4);

	top.setP(P + dt*weightedDP);
	top.setDP(DP + dt*weightedDDP);
}



