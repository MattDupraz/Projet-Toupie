#include "vect.h"
#include "top.h"

class Integrator{
	public:
		virtual void evolve(Top& top, double dt) = 0;
};


class EulerCromerIntegrator : public Integrator{
	public : 
		virtual void evolve(Top& top, double dt) override;
};


class NewmarkIntegrator : public Integrator{
	public :
		virtual void evolve(Top& top, double dt) override;
	
		void setPrecision(double t){ epsilon = t; }
		double getPrecsion(){ return epsilon; }
	
	private : 
		double epsilon;
};


class RungeKuttaIntegrator : public Integrator{
	public:
		virtual void evolve(Top& top, double dt) override;
};
