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
		System(System const&) = delete;
		System& operator=(System const&) = delete;

		virtual void draw() const override {
			view_->draw(*this);
		}

		void evolve(double dt){
			t += dt;
			for (std::unique_ptr<Top>& top : tops){
				integrator->evolve(*top, dt);
			}
		}

		void add(std::unique_ptr<Top> t) {
			tops.push_back(std::move(t));
		}

		const Top& getTop(std::size_t n) const { return *tops[n]; }
		std::size_t size() const { return tops.size(); }

		double getElapsedTime() const { return t; };

	private :
		std::vector<std::unique_ptr<Top>> tops;
		std::shared_ptr<Integrator> integrator;

		double t;
};

std::ostream &operator<<(std::ostream& os, System const& system);
