#pragma once

#include "vect.h"
#include "drawable.h"
#include "view.h"
#include "integrator.h"


class Top : public Drawable {
	public:
		Top(View* v, double mass = 0.0, //Matrix3x3 const& tensor,
			Vector const& pos = Vector(3), Vector const& vel = Vector{0, 0, 5},
			Vector const& angPos = Vector(3), 
			Vector const& angVel = Vector{50, 20, 100}, 
			integrator& i=EulerCromerIntegrator()  )
			: Drawable(v), pos_(pos), vel_(vel),
				angPos_(angPos), angVel_(angVel),
				//tensorInert_(tensor), mass_(mass)
				mass_(mass), integ(i)
		{}



		virtual ~Top() {}

		virtual void draw() override {
			view_->draw(*this);
		}



		Vector const& getPos() const { return pos_; }
		Vector getVel() const { return vel_; }
		Vector getAngPos() const { return angPos_; }
		Vector getAngVel() const { return angVel_; }
		//Matrix3x3 getTensorInert() const { return tensorInert_; }
		double getMass() const { return mass_; }

		void update();


	private:
		

		Vector pos_; // Spatial coordinates
		Vector vel_; // Velocity vector
		Vector angPos_; // Angular position vector (Euler coordinates)
		Vector angVel_; // Angular velocity vector (Euler coordinates)
		//Matrix3x3 const tensorInert_; // Moment of inertia tensor
		double const mass_;
		// Integrator
		Integrator integ;
};






