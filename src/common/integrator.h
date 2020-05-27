#pragma once
#include "top.h"

// Classe de base pour les intégrateurs
class Integrator{
	public:
		// Méthode évolue une toupie en fonction du pas de temps
		virtual void evolve(Top& top, double dt) = 0;
		
};





