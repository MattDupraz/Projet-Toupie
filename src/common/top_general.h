#pragma once
#include "top.h"

class GeneralTop : public Top{
	// P = [psi, theta, phi, antiderivative of x, antiderivative of y]
	public:
		GeneralTop(std::shared_ptr<View> v,
			Vector const& P, Vector const& DP,
			double rho, Vector layers, double thickness);

		// Retourne la seconde derivee
		virtual Vector getDDP(Vector P, Vector DP) override;	

		// Retourne les angles d'euler
		double psi() const override { return P_[0]; }
		double theta() const override { return P_[1]; }
		double phi() const override { return P_[2]; }

		// Retourne les coordonnees du point de contact
		double x() const override { return DP_[3]; }
		double y() const override { return DP_[4]; }
		double z() const override { return 0; }
		
		double dx() const override { return DDP_cache[3];}
		double dy() const override { return DDP_cache[4];}
		double dz() const override { return 0;}

		virtual double getMomentInertia_xy() const override { return I_1; }
		virtual double getMomentInertia_z() const override { return I_3; }

		virtual Vector getAG() const override;

		// Retourne les derivees des angles d'euler
		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }

		// Retourne la distance du centre de masse du point de contact
		double getDistAG() const { return d; }
		// Retourne la masee
		double getMass() const { return m; }

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
		
		// Différents accesseurs
		Vector getLayers() const { return layers; }
		double getHeight() const { return L*layers.size(); }
		double getThickness() const { return L; }
		double getDensity() const { return rho; }

	private:
		double rho;	// La masse volumique des cylindres
		double L;	// L'épaisseur des cylindres
		Vector layers;	// Les rayons de chaque cylindre

		double m; // Mass
		double d; // Distance from contact point to center of mass
		double I_1; // Moment of inertia - horizontal axes
		double I_3; // Moment of inertia - vertical axis

		// Saves DDP so we don't reevaluate when we need d_x and d_z
		Vector DDP_cache = Vector(std::size_t(5));
};
