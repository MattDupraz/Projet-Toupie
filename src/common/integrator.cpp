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
		
	Vector s(top.getDDP());
	Vector q(top.getP());
	
	do{
		Vector q(top.getP());
		
		Vector u(top.getDP());
		
		Vector r(top.getDDP());
		
		top.setDP(r+dt*0.5*(r+s));
		
		top.setP(q+dt*u+dt*dt/3*(0.5*r+s));
		
		}while((top.getP()- q ).norm()>=epsilon);

}

void RungeKuttaIntegrator::evolve(
		Top& top, double dt){
	
}



