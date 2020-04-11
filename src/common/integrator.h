#pragma once
#include "vect.h"
#include "top.h"

// Classe de base pour les integrateurs
class Integrator{
	public:
		// Methode evolue une toupie en fonction du pas de temps
		virtual void evolve(Top& top, double dt) = 0;
		
};

// Methode d'Euler
class EulerCromerIntegrator : public Integrator{
	public : 

		virtual void evolve(Top& top, double dt) override;
};

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


// Methode Runge-Kutta
class RungeKuttaIntegrator : public Integrator{
	public:

		virtual void evolve(Top& top, double dt) override;
};
