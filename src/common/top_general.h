#pragma once
#include "top.h"

// Toupie générale - approximation d'un solide de révolution, avec
// la dérivée seconde de P `proprement` calculée
class GeneralTop : public Top{
	// P = [psi, theta, phi, primitive de x, primitive de y]
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
		
		// Dérivées de x, y, z resp.
		double dx() const override { return DDP_cache[3];}
		double dy() const override { return DDP_cache[4];}
		double dz() const override { return 0;}

		// Moments d'inertie par rapport aux axes principaux
		virtual double getMomentInertia_xy() const override { return I_1; }
		virtual double getMomentInertia_z() const override { return I_3; }

		// Vecteur AG
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
		
		// Les valeur numériques du rayon à chaque couche de la toupie
		Vector getLayers() const { return layers; }
		// Hauteur de la toupie
		double getHeight() const { return L*layers.size(); }
		// Hauteur des couches
		double getThickness() const { return L; }
		// Masse volumique
		double getDensity() const { return rho; }

	private:
		double rho;	// La masse volumique des cylindres
		Vector layers;	// Les rayons de chaque cylindre
		double L;	// L'épaisseur des cylindres

		double m; // Masse
		double d; // Distance AG
		double I_1; // Moment d'inertie - axes horizontaux
		double I_3; // Moment of inertia - axe vertical

		// Sauvegarde DDP pour ne pas devoir à le recalculer pour l'affichage
		Vector DDP_cache = Vector(std::size_t(5));
};
