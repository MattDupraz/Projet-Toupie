#pragma once

#include "vect.h"
#include "drawable.h"

class Top : public Drawable {
	public:
		Top(View* v)
			: Drawable(v)
		{}

		Top(View* v, double mass, Matrix3x3 const& tensor,
				Vector const& pos = Vector(), Vector const& vel = Vector(),
				Vector const& angPos = Vector(), Vector const& angVel = Vector())
			: Top(v), pos_(pos), vel_(vel),
				angPos_(angPos), angVel_(angVel),
				tensorInert_(tensor), mass_(mass)
		{}

		virtual ~Top() {}

		virtual void draw() override {
			view->draw(*this);
		}

		Vector getPos() const { return pos_; }
		Vector getVel() const { return vel_; }
		Vector getAngPos() const { return angPos_; }
		Vector getAngVel() const { return angVel_; }
		Matrix3x3 getTensorInert() const { return tensorInert_; }
		double getMass() const { return mass_; }

		void update(double dt);

	private:
		Vector pos_; // Spatial coordinates
		Vector vel_; // Velocity vector
		Vector angPos_; // Angular position vector (Euler coordinates)
		Vector angVel_; // Angular velocity vector (Euler coordinates)
		Matrix3x3 const tensorInert_; // Moment of inertia tensor
		double const mass_;
}