#pragma once
#include "vect.h"
#include "top.h"

// Classe de base pour les integrateurs
class Integrator{
	public:
		// Methode evolue une toupie en fonction du pas de temps
		virtual void evolve(Top& top, double dt) = 0;
		
};





