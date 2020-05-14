#pragma once

#include "top.h"

class ChineseTop : public Top {
	// P = [psi, theta, phi, antiderivative of x, antiderivative of y]
	public:	
		ChineseTop(std::shared_ptr<View> v,
				Vector const& P,	Vector const& DP,
				double rho, double R, double h);

		// Retourne la seconde derivee
		virtual Vector getDDP(Vector P, Vector DP) override;	

		// Retourne les angles d'euler
		double psi() const override { return P_[0]; }
		double theta() const override { return P_[1]; }
		double phi() const override { return P_[2]; }

		double x() const override { return DP_[3]; }
		double y() const override { return DP_[4]; }
		double z() const override { return 0; }

		// Retourne les derivees des angles d'euler
		double d_psi() const override { return DP_[0]; }
		double d_theta() const override { return DP_[1]; }
		double d_phi() const override { return DP_[2]; }

		// Retourne les dérivées des coordonnees des points de contacts
		double dx() const override { return DDP_cache[3]; }
		double dy() const override { return DDP_cache[4]; }
		double dz() const override { return 0; }

		double getMomentInertia_xy() const override { return I_1; }
		double getMomentInertia_z() const override { return I_3; }

		// Retourne la masee
		double getMass() const override { return m; }
		// Retourne la hauteur du CM par rapport au centre de la sphere
		
		Vector getAG() const override;

		// Retourne le rayon de la sphere
		double getRadius() const { return R; }
		// Retourne la hauteur tronquée
		double getTruncatedHeight() const { return h; }
		// Retourne la masse volumique
		double getDensity() const { return rho; }

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;

	protected:	
		double h; // truncated height
		double R; // sphere radius
		double rho; // density
		double m; // Mass
		double alpha; //Distance from center of mass from center of sphere
		// Moments of inertia with respect to A (point of contact)
		double I_1; // Moment of inertia - horizontal axis
		double I_3; // Moment of inertia - vertical axis

		// Saves DDP so we don't reevaluate when we need d_x and d_z
		Vector DDP_cache = Vector(std::size_t(5));
};
