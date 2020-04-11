#pragma once

#include "top.h"
#include "integrator.h"
#include "drawable.h"

#include <vector>
#include <ostream>

class System : public Drawable {
	public :
		System(std::shared_ptr<View> v, std::shared_ptr<Integrator> i)
			:Drawable(std::move(v)),integrator(std::move(i))
		{}
		// On ne permet pas la copie du systeme
		System(System const&) = delete;
		System& operator=(System const&) = delete;

		// Methode pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Evolue le systeme en fonction du pas de temps dt
		void evolve(double dt){
			t += dt;
			for (std::unique_ptr<Top>& top : tops){
				integrator->evolve(*top, dt);
			}
		}

		// Ajoute une toupie au systeme
		void add(std::unique_ptr<Top> t) {
			tops.push_back(std::move(t));
		}

		// Retourne une reference constante a une toupie du systeme
		const Top& getTop(std::size_t n) const { return *tops[n]; }
		// Retourne le nombre de touipes du systeme
		std::size_t size() const { return tops.size(); }

		// Retourne le temps total ecoule depuis le debut de la simulation
		double getElapsedTime() const { return t; };

	private :
		// Liste dynamique de toupies du systeme
		std::vector<std::unique_ptr<Top>> tops;
		// Integrateur utilise
		std::shared_ptr<Integrator> integrator;

		double t;

};



// Affiche les details du systeme dans le ostream fourni
std::ostream &operator<<(std::ostream& os, System const& system);
