#pragma once
#include "top.h"

// Toupie abstraite qui ne roule pas
class NonRollingTop : public Top {
	// P = [psi, theta, phi]
	public:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A, 
				Vector const& P,	Vector const& DP,
				double m, double d, double I_1, double I_3)
			: Top(std::move(v), P, DP), A(A), m(m), d(d), I_1(I_1), I_3(I_3)
		{}

		// Retourne la seconde derivee de P
		virtual Vector getDDP(Vector P, Vector DP) override;	

		// Retourne les angles d'euler
		double psi() const override { return P_[0]; }
		double theta() const override { return P_[1]; }
		double phi() const override { return P_[2]; }

		// Retourne les coordonnees du point de contact
		double x() const override { return A[0]; }
		double y() const override { return A[1]; }
		double z() const override { return A[2]; }
		
		// Dérivées de x, y, z resp. (nulles, car la toupie ne bouge pas)
		double dx() const override { return 0;}
		double dy() const override { return 0;}
		double dz() const override { return 0;}

		// Moments d'inertie en G par rapport aux axes principaux
		virtual double getMomentInertia_xy() const override { return I_1; }
		virtual double getMomentInertia_z() const override { return I_3; }
		// Moment d'inertie en A par raport aux axes horizontaux
		double getMomentInertiaA_xy() const;

		virtual Vector getAG() const override;

		// Retourne les derivees des angles d'euler
		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }

		// Retourne la distance du centre de masse du point de contact
		double getDistAG() const { return d; }
		// Retourne la masee
		double getMass() const { return m; }

		// Retourne le vecteur position du point de contact
		Vector getOrigin() const { return A; }

	protected:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP)
			: Top(std::move(v), P, DP), A(A)
		{}

		Vector A; // Position du point de contact

		double m; // Masse
		double d; // Distance AG
		double I_1; // Moment d'inertie par rapport aux axes horizontaux
		double I_3; // Moment d'inertie par rapport à l'axe vertical
};
