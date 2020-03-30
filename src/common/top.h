#pragma once

#include <ostream>

#include "vect.h"
#include "drawable.h"
#include "view.h"
#include "matrix_3x3.h"

class Top : public Drawable {
	public:
		unsigned int objectID;

		Top(std::shared_ptr<View> view, Vector const& P, Vector const& DP)
			: Drawable(std::move(view)), P_(P), DP_(DP)
		{
			static unsigned int counter;
			objectID = ++counter;
		}

		virtual ~Top() {}

		// Getters and setters
		Vector getP() const { return P_; }
		Vector getDP() const { return DP_; }
		void setP(Vector const& P) { P_ = P; }
		void setDP(Vector const& DP) { DP_ = DP; } 
		
		// Returns the second derivative
		virtual Vector getDDP(Vector P, Vector DP) const = 0;

		virtual std::ostream& print(std::ostream& os) const = 0;

	protected :	
		Vector P_; // Degrees of freedom
		Vector DP_; // First derivative of P
	private :
};

std::ostream &operator<<(std::ostream& os, Top const& a);

class NonRollingTop : public Top {
	// P = [psi, theta, phi]
	public:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A, 
				Vector const& P,	Vector const& DP,
				double m, double d, double I_A1, double I_A3)
			: Top(std::move(v), P, DP), A(A), m(m), d(d), I_A1(I_A1), I_A3(I_A3)
		{}

		virtual Vector getDDP(Vector P, Vector DP) const override;	

		double psi() const { return P_[0]; }
		double theta() const { return P_[1]; }
		double phi() const { return P_[2]; }

		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }

		double getHeightCM() const { return d; }
		double getMass() const { return m; }

		Vector getOrigin() const { return A; }
	protected:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP)
			: Top(std::move(v), P, DP), A(A)
		{}

		Vector A; // Contact point

		double m; // Mass
		double d; // Distance from contact point to center of mass
		// Moments of inertia with respect to A (point of contact)
		double I_A1; // Moment of inertia - horizontal axes
		double I_A3; // Moment of inertia - vertical axis
};

class SimpleCone : public NonRollingTop {
	public:
		// rho = masse volumique
		// L = hauteur 
		// R = rayon a la base
		SimpleCone(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double rho, double L, double R);

		virtual void draw() const override {
			view_->draw(*this);
		}

		double getDensity() const { return rho; };
		double getHeight() const { return L; };
		double getRadius() const { return R; };

		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho;
		double L;
		double R;
};

class Gyroscope : public NonRollingTop {
	public:
		Gyroscope(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double d, double rho, double L, double R);

		virtual void draw() const override {
			view_->draw(*this);
		}

		double getDensity() const { return rho; }
		double getThickness() const { return L; }
		double getRadius() const { return R; }
		double getHeight() const { return d; }

		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho;
		double L;
		double R;
};
