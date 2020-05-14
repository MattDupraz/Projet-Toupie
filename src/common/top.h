#pragma once

#include <ostream>

#include "vect.h"
#include "drawable.h"
#include "view.h"
#include "matrix_3x3.h"

class Top : public Drawable {
	public:
		// Identifiant unique de la toupie
		unsigned int objectID;

		Top(std::shared_ptr<View> view, Vector const& P, Vector const& DP)
			: Drawable(std::move(view)), P_(P), DP_(DP)
		{
			// Fait en sorte que chaque vecteur a un ID unique
			// Ceci est utilise pour identifier les toupies lors du dessin
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
		virtual Vector getDDP(Vector P, Vector DP) = 0;

		// Getters for euler angles of the top
		virtual double psi() const = 0;
		virtual double theta() const = 0;
		virtual double phi() const = 0;

		virtual double d_psi() const = 0;
		virtual double d_theta() const = 0;
		virtual double d_phi() const = 0;
		
		// Getters for coordinates of the top (contact point)
		virtual double x() const = 0;
		virtual double y() const = 0;
		virtual double z() const = 0;

		virtual double dx() const = 0;
		virtual double dy() const = 0;
		virtual double dz() const = 0;

		// Height of the center of mass
		virtual double getHeightG() const = 0;

		// Moments of inertia around principal axes
		virtual double getI_xy() const = 0;
		virtual double getI_z() const = 0;

		virtual double getMass() const = 0;

		double getI_Axy() const;

		Vector getPosA() const;
		Vector getPosG() const;
		Vectir getAG() const;
		Vector getVelocityA() const;
		Vector getVelocityG() const;

		Vector getAngVelocity() const;

		// Matrix of inertia	
		Matrix3x3 getInertiaMatrixG() const;
		Matrix3x3 getInertiaMatrixA() const;
		// Matrix of basis change from top's reference frame
		// to inertial reference fram
		Matrix3x3 getOrientationMatrix() const;


		// Affiche les parametres de la toupie dans le ostream
		virtual std::ostream& print(std::ostream& os) const = 0;

		double getEnergy() const;
		Vector getAngMomentumA() const;
		Vector getAngMomentumG() const;

	protected :	

		Vector P_; // Degrees of freedom
		Vector DP_; // First derivative of P
	private :
};

// Affiche les parametres de la toupie dans le ostream
std::ostream &operator<<(std::ostream& os, Top const& a);
