#pragma once

#include <ostream>
#include <cmath>

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
		
		// Getters for euler angles of the top
		virtual double psi() const { return 0; }
		virtual double theta() const { return 0; }
		virtual double phi() const { return 0; }
		
		// Getters for coordinates of the top (contact point)
		virtual double x() const { return 0; }
		virtual double y() const { return 0; }
		virtual double z() const { return 0; }

		virtual double getHeightCM() const { return 0; }
		
		// Returns the second derivative
		virtual Vector getDDP(Vector P, Vector DP) = 0;

		// Affiche les parametres de la toupie dans le ostream
		virtual std::ostream& print(std::ostream& os) const = 0;

		virtual double getEnergy()const = 0;
		virtual double getL_Ak()const = 0;
		virtual double getL_Aa()const = 0;

	protected :	
		Vector P_; // Degrees of freedom
		Vector DP_; // First derivative of P
	private :
};

// Affiche les parametres de la toupie dans le ostream
std::ostream &operator<<(std::ostream& os, Top const& a);

class NonRollingTop : public Top {
	// P = [psi, theta, phi]
	public:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A, 
				Vector const& P,	Vector const& DP,
				double m, double d, double I_A1, double I_A3)
			: Top(std::move(v), P, DP), A(A), m(m), d(d), I_A1(I_A1), I_A3(I_A3)
		{}

		// Retourne la seconde derivee
		virtual Vector getDDP(Vector P, Vector DP) override;	

		// Retourne les angles d'euler
		double psi() const override { return P_[0]; }
		double theta() const override { return P_[1]; }
		double phi() const override { return P_[2]; }

		// Retourne les coordonnees du point de contact
		double x() const override { return A[0]; }
		double y() const override { return A[1]; }
		double z() const override { return A[2]; }

		// Retourne les derivees des angles d'euler
		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }

		// Retourne la distance du centre de masse du point de contact
		double getHeightCM() const { return d; }
		// Retourne la masee
		double getMass() const { return m; }

		// Retourne le vecteur position du point de contact
		Vector getOrigin() const { return A; }

		// Retourne l'énergie
		virtual double getEnergy()const override;
		// Retourne le moment cinétique en A
		virtual double getL_Ak()const override;
		virtual double getL_Aa()const override{return Vector{0,0,1}*getDP();}
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

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}
		
		// Accesseurs aux parametres du cone
		double getDensity() const { return rho; };
		double getHeight() const { return L; };
		double getRadius() const { return R; };

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho; // Densite volumique du cone
		double L; // Hauteur du cone
		double R; // Rayon de la base
};


class ToupiesGen : public NonRollingTop{
	public:
		ToupiesGen(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double rh, Vector rays, double th)
		:NonRollingTop(std::move(v), A, P, DP), rho(rh), rayons(rays), thick(th)
		{
		L = thick*rayons.size();
		this->masse_calcul();
		this->center_mass();
		this->CalculInertie();
		}
		
		// Les différents calculs nécessaires pour les toupies générales
		void masse_calcul();
		void center_mass();		
		void CalculInertie();

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			//view_->draw(*this);
		}

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
		
		// Différents accesseurs
		Vector getRayons()const{return rayons;}
		double getThick()const{return thick;}
		double getDensity()const{return rho;}

private:
	double rho;	// La masse volumique des cylindres
	Vector rayons;	// Les rayons de chaque cylindre
	double thick;	// L'épaisseur des cylindres
	double L;	// Longueur de la toupie
};


class Gyroscope : public NonRollingTop {
	public:
		Gyroscope(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double d, double rho, double L, double R);

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Accesseurs aux variables du gyroscope
		double getDensity() const { return rho; }
		double getThickness() const { return L; }
		double getRadius() const { return R; }
		double getHeight() const { return d; }

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho; // Densite volumique de disque
		double L; // Largeur du disque
		double R; // Rayon du disque
};


class ChineseTop : public Top {
	// P = [psi, theta, phi, antiderivative of x, antiderivative of z]
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

		// Retourne les coordonnees du centre de la sphere
		double x() const override { return DP_[3]; }
		double y() const override { return getRadius(); }
		double z() const override { return DP_[4]; }

		// Retourne les derivees des angles d'euler
		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }
		// Retourne les dérivées des coordonnees des points de contacts
		double d_x() const { return DDP_cache[3]; }
		double d_z() const { return DDP_cache[4]; }

		// Retourne le rayon de la sphere
		double getRadius() const { return R; }
		// Retourne la masee
		double getMass() const { return m; }
		// Retourne la hauteur tronquée
		double getTruncatedHeight() const { return h; }
		// Retourne la masse volumique
		double getDensity() const { return rho; }
		// Retourne la hauteur du CM par rapport au centre de la sphere
		double getHeightCM() const { return - R * alpha; }

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;

		virtual double getEnergy()const override;
		virtual double getL_Ak()const override{Vector a{psi(),thet(),phi()};return Vector{0,0,1}*a;}
		virtual double getL_Aa()const override;
	protected:	
		double h; // truncated height
		double R; // sphere radius
		double rho; // density
		double m; // Mass
		double alpha; //Distance from center of mass from center of sphere
		// Moments of inertia with respect to A (point of contact)
		double I_1; // Moment of inertia - horizontal axes
		double I_3; // Moment of inertia - vertical axis

		// Saves DDP so we don't reevaluate when we need d_x and d_z
		Vector DDP_cache = Vector(std::size_t(5));

};
