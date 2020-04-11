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

		Top(std::shared_ptr<View> view, Vector const& P, Vector const& DP, const char* add="")
			: Drawable(std::move(view)), P_(P), DP_(DP), address(add)
		{
			// Fait en sorte que chaque vecteur a un ID unique
			// Ceci est utilise pour identifier les toupies lors du dessin
			static unsigned int counter;
			objectID = ++counter;

			time=0;
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
		
		// Returns the second derivative
		virtual Vector getDDP(Vector P, Vector DP) const = 0;

		// Affiche les parametres de la toupie dans le ostream
		virtual std::ostream& print(std::ostream& os) const = 0;

		// Return the address of the file
		const char* getAddress()const{return address;}

		// Return the time
		double getTime()const{return time;}

		// Set the time 
		void setTime(double t){time =t;}

	protected :	
		const char* address;
		double time;
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
				double m, double d, double I_A1, double I_A3, const char* add="")
			: Top(std::move(v), P, DP,add), A(A), m(m), d(d), I_A1(I_A1), I_A3(I_A3)
		{}

		// Retourne la seconde derivee
		virtual Vector getDDP(Vector P, Vector DP) const override;	

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
	protected:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP, const char* add)
			: Top(std::move(v), P, DP, add), A(A)
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
				double rho, double L, double R, const char* add="");

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

class Gyroscope : public NonRollingTop {
	public:
		Gyroscope(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double d, double rho, double L, double R, const char* add="");

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
