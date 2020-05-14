#pragma once
#include "integrator.h"

// Methode Runge-Kutta
class RungeKuttaIntegrator : public Integrator{
	public:

		virtual void evolve(Top& top, double dt) override;
};
