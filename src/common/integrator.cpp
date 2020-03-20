#include <iostream>
#include "vect.h"

void EulerCromerIntegrator::integ(Vector& pos, 
								  Vector& vel, 
								  Vector& acc,
								  double dt){
	vel =vel+ dt*acc;
	pos =pos+ dt*vel;
	}


void Newmark::integ(Vector& pos, 
					Vector& vel, 
					Vector& acc,
					double dt){

	
}



void Runge_Kutta::integ(Vector& pos, 
					Vector& vel, 
					Vector& acc,
					double dt){

	
}



