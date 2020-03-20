#include "top.h"
#include "vect.h"
#include "view.h"

void Top::update(double dt) {
	pos_ += freeDegree_*dt;
	angPos_ += DegreeDerivative_*dt;
}


void ConeSimple::init_tendor(double length, double radius){
	double r(radius*radius);
	double l(length*length);
	
	tensorInert_= {{mass_*(3/20*r+3/5*l),0,0},{0,0,0},{0,0,3*mass_*(r/10 +3*l/16)}};
}
