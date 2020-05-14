#pragma once
#include "top_non_rolling.h"

class GeneralTop : public NonRollingTop{
	public:
		GeneralTop(std::shared_ptr<View> v, Vector const& A,
			Vector const& P, Vector const& DP,
			double rho, Vector layers, double thickness);

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
	
	// Les différents calculs nécessaires pour les toupies générales
	void init_mass();
	void init_CM();		
	void init_I_A();
};
