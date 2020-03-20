#pragma once

#include "vect.h"
#include "drawable.h"
#include "view.h"
#include "integrator.h"
#include "matrix3x3.h"


class Top : public Drawable {
	public:
		Top(View* v, double mass = 0.0, Vector const& fd = Vector(5), 
			Vector const& dd = Vector(5),
			integrator& i=EulerCromerIntegrator()  )
			: Drawable(v), freeDegree_(fd), DegreeDerivative_(dd),
			  mass_(mass), integ(i)
		{}



		virtual ~Top() {}

		virtual void draw() override {
			view_->draw(*this);
		}

		Vector getFD(){return freeDegree;}

		Vector getDD(){return DegreeDerivative;}

		
		double getMass() const { return mass_; }

		void update(double dt);

	protected :
		

		Vector freeDegree_; // Spatial coordinates + Euler's angle
		Vector DegreeDerivative_; // The derivative of the precedant vector
		
		 
		Matrix3x3 const tensorInert_; // Moment of inertia tensor
		double const mass_;
		Integrator* integ;
};


class ConeSimple : public Top{
	private :
		Matrix3x3 const tensorInert_={};



	public :

		ConeSimple(View* v, double mass = 0.0, Vector const& fd = Vector(5), 
			Vector const& dd = Vector(5),
			integrator& i=EulerCromerIntegrator()  )
			: Top(v,mass,fd,ff,i)
		{}


	void init_tendor(double length, double raduis);






};








