#pragma once
#include "top_non_rolling.h"

// Gyroscope = un disque en rotation soutenu par une tige négligeable
class Gyroscope : public NonRollingTop {
	public:
		Gyroscope(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double d, double rho, double L, double R);

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Masse volumique
		double getDensity() const { return rho; }
		// Épaisseur du disque
		double getThickness() const { return L; }
		// Rayon du disque
		double getRadius() const { return R; }
		// Hauteur du disque (distance AG)
		double getHeight() const { return d; }

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho; // Densite volumique de disque
		double L; // Largeur du disque
		double R; // Rayon du disque
};
