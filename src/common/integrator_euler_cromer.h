#pragma once
#include "integrator.h"

// Methode d'Euler
class EulerCromerIntegrator : public Integrator{
	public : 
		virtual void evolve(Top& top, double dt) override;
};

