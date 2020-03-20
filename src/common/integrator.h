#include "vect.h"

class Integrator{
	virtual void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc,
			   double dt);
	
};


class EulerCromerIntegrator : public Integrator{
	public : 
		void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc,
			   double dt);
	
};


class Newmark : public Integrator{
	public :
		void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc,
			   double dt);
	
		void setPrecision(double t){epsilon = t;}
		double getPrecsion(){return epsilon;}
	
	private : 
		double epsilon;
};


class Runge_Kutta : public Integrator{


		void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc,
			   double dt);



};
