#include "vect.h"

class Integrator{
	protected :
	double dt;
	public :
	Integrator(double num=0.1)
	:dt(num){}
	
};


class EulerCromerIntegrator : public Integrator{
	public : 
	void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc);
	
	EulerCromerIntegrator(double num)
	:Integrator(num){}
};


class Newmark : public Integrator{
	public :
	void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc);
	
	Newmark(double num, double epsilon=1e-10)
	:Integrator(num){}
	
	void setPrecision(double t){epsilon = t;}
	double getPrecsion(){return epsilon;}
	
	private : 
	double epsilon;
};
