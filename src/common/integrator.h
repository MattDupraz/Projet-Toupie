#include "vect.h"

class Integrator{
	virtual void integVector& pos, 
			   Vector& vel, 
			   Vector& acc)=0;
	
};


class EulerCromerIntegrator : public Integrator{
	public : 
	void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc
			   double dt);
	
};


class Newmark : public Integrator{
	public :
	void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc
			   double dt);
	
	void setPrecision(double t){epsilon = t;}
	double getPrecsion(){return epsilon;}
	
	private : 
	double epsilon;
};
