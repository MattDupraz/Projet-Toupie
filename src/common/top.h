#pragma once

#include <ostream>

#include "vect.h"
#include "drawable.h"
#include "view.h"
#include "matrix_3x3.h"

// Classe toupie, définie une toupie abstraite (objet 3D en rotation)
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
		
		// Accésseurs pour les degrés de liberté et leur dérivée
		Vector getP() const { return P_; }
		Vector getDP() const { return DP_; }
		void setP(Vector const& P) { P_ = P; }
		void setDP(Vector const& DP) { DP_ = DP; } 

		// Deuxième dérivée de P en fonction de P et DP
		virtual Vector getDDP(Vector P, Vector DP) = 0;
		
		// Tous les accesseurs suivants doivent être implémentés par
		// les sous-classes, car chaque type de toupie peux traiter
		// ces varirables différement et cela dépend aussi du vecteur P

		// Accesseurs pour les angles d'Euler
		virtual double psi() const = 0;
		virtual double theta() const = 0;
		virtual double phi() const = 0;

		// Accesseurs pour les dérivées des angles d'Euler
		virtual double d_psi() const = 0;
		virtual double d_theta() const = 0;
		virtual double d_phi() const = 0;
		
		// Accesseurs pour les coordonnees du point de contact avec le sol
		virtual double x() const = 0;
		virtual double y() const = 0;
		virtual double z() const = 0;

		// Accesseurs pour les dérivées de x, y, z resp.
		virtual double dx() const = 0;
		virtual double dy() const = 0;
		virtual double dz() const = 0;

		// Moments d'inertie par rapport aux axes principaux
		virtual double getMomentInertia_xy() const = 0;
		virtual double getMomentInertia_z() const = 0; // Axe de symétrie

		// Accesseur pour la masse de la toupie
		virtual double getMass() const = 0;

		// Accesseur pour le vecteur AG
		virtual Vector getAG() const = 0;

		// Méthodes utiles pour les calculs:
		
		// Position du point de contact
		Vector getPosA() const;
		// Position du centre de masse
		Vector getPosG() const;
		// Vitesse du point de contact
		Vector getVelocityA() const;
		// Vitesse du centre de masse
		Vector getVelocityG() const;

		// Vitesse angulaire (dans le repère de la toupie)
		Vector getAngVelocity() const;

		// Tenseurs d'inertie (dans le repère de la toupie)
		Matrix3x3 getInertiaMatrixG() const; // Par rapport à G
		Matrix3x3 getInertiaMatrixA() const; // Par rapport à A
		Matrix3x3 getInertiaMatrix(Vector const&) const; // Par rapport à un point quelconque
		// Matrice de passage du repère de la toupie, au repère d'inertie
		Matrix3x3 getMatrixToGlobal() const;
		// Matrice de passage du repère d'inertie, au repère de la toupie
		Matrix3x3 getMatrixFromGlobal() const;


		// Affiche les parametres de la toupie dans le ostream
		virtual std::ostream& print(std::ostream& os) const = 0;

		// Energie totale de la toupie
		double getEnergy() const;
		// Moment cinétique par rapport à A (repère de la toupie)
		Vector getAngMomentumA() const;
		// Moment cinétique par rapport à G (repère de la toupie)
		Vector getAngMomentumG() const;
		// Coordonnée z du produit vectoriel entre la vitesse
		// angulaire et moment cinétique en G (repère de la toupie)
		double getMixedProduct() const;

	protected :	
		Vector P_; // Degrés de liberté
		Vector DP_; // Dérivée première des degrés de liberté
	private :
};

// Affiche les parametres de la toupie dans le ostream
std::ostream &operator<<(std::ostream& os, Top const& a);
