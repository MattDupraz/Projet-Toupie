#pragma once

#include "top.h"

class ChineseTop : public Top {
	// P = [psi, theta, phi, primitive de x, primitive de y]
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
		double h; // Hauteur tronquée
		double R; // Rayon de la sphère
		double rho; // Masse volumique
		double m; // Masse
		double alpha; // 1/R * Distance CG
		double I_1; // Moment d'inertie - axes horizontales
		double I_3; // Moment d'inertie - axe vertical

		// Sauvegarde DDP pour ne pas devoir à le recalculer pour l'affichage
		Vector DDP_cache = Vector(std::size_t(5));
};
