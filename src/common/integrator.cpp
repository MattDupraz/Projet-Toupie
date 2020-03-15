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
	
	Vector q(pos);
	//Vector (vel);
	Vector a(acc);
	
	do{
		vel= vel+(dt/2)*() 
	
	
	}while();

