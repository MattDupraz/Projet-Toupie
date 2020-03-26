#pragma once

#include "vect.h"
#include "drawable.h"
#include "view.h"
#include "matrix_3x3.h"

class Top : public Drawable {
	public:
		Top(View* v, Vector const& P, 
			Vector const& DP)
			: Drawable(v), P_(P), DP_(DP)
		{}

		virtual ~Top() {}

		// Getters and setters
		Vector getP() const { return P_; }
		Vector getDP() const { return DP_; }
		void setP(Vector const& P) { P_ = P; }
		void setDP(Vector const& DP) { DP_ = DP; } 
		
		// Returns the second derivative
		virtual Vector getDDP(Vector P, Vector DP) const = 0;

	protected :	
		Vector P_; // Degrees of freedom
		Vector DP_; // First derivative of P
};

class Gyroscope : public Top {
	// P = [psi, theta, phi]
	public:	
		Gyroscope(View* v, Vector const& P,	Vector const& DP,
				double m, double d, double I_A1, double I_A3)
			: Top(v, P, DP), m(m), d(d), I_A1(I_A1), I_A3(I_A3)
		{}

		virtual Vector getDDP(Vector P, Vector DP) const override;	

		double psi() const { return P_[0]; }
		double theta() const { return P_[1]; }
		double phi() const { return P_[2]; }

		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }

		double getMass() const { return m; }
	protected:	
		Gyroscope(View* v, Vector const& P,	Vector const& DP)
			: Top(v, P, DP)
		{}

		double m; // Mass
		double d; // Distance from contact point to center of mass
		// Moments of inertia with respect to A (point of contact)
		double I_A1; // Moment of inertia - horizontal axes
		double I_A3; // Moment of inertia - vertical axis
};

class SimpleCone : public Gyroscope {
	public:
		// rho = masse volumique
		// L = hauteur 
		// R = rayon a la base
		SimpleCone(View* v, Vector const& P, Vector const& DP,
				double rho, double L, double R);

		virtual void draw() override {
			view_->draw(*this);
		}

		double getDensity() const { return rho; };
		double getHeight() const { return L; };
		double getRadius() const { return R; };
	private:
		double rho;
		double L;
		double R;
};
