#pragma once

#include "integrator.h"

// Methode de Newmark
class NewmarkIntegrator : public Integrator{
	public :
		NewmarkIntegrator(double eps=0.002)
			:epsilon(eps){}
			
		virtual void evolve(Top& top, double dt) override;
	
		// Accesseurs pour la precision utilisee
		void setPrecision(double t){ epsilon = t; }
		double getPrecsion(){ return epsilon; }
	
	private : 
		double epsilon;
};
