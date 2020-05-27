#pragma once

#include <vector>
#include <ostream>
#include <initializer_list>

// Exception lors des operation erronnees
enum VectorException { VECTOR_INDEX_OUT_OF_BOUNDS, INCOMPATIBLE_VECTOR_SIZE };

// Vecteur de taille dynamique contenant des doubles
class Vector {
	public:
		// Construit un vecteur de dimension 0
	  	Vector() {}
	  	// Constrit un vecteur contenant les valeurs de l
		Vector(std::initializer_list<double> l)
			: coords_(l)
		{}
		// Construit un vecteur nul de dimension s
		Vector(std::size_t s)
			: coords_(s, 0.0)
		{}
	
		// Ajoute une dimension au vecteur (avec la valeur fournie)
		Vector& augment(double val);
		// Retourne la norme du vecteur
		double norm() const;
		// Retourne la norme du vecteur caree
		double norm2() const;

		// Retourne la dimension du vecteur
		std::size_t size() const { return coords_.size(); }
		
		// Accesseurs aux coordonnees du vecteur
		double operator[](std::size_t i) const;
		double& operator[](std::size_t i);
		
		// Multiplie ce vecteur par un scalaire
		Vector& operator*=(double d);
		// Additionne un vecteur a celui ci
		Vector& operator+=(Vector const& v);
		// Soustrait un vecteur de celui ci
		Vector& operator-=(Vector const& v);

	private:
		std::vector<double> coords_;

};

std::ostream &operator<<(std::ostream& os, Vector const& v);

// Operations sur les vecteurs
Vector operator*(double d, Vector v); // Multiplication par un scalaire
Vector operator*(Vector v, double d); // Multiplication par un scalaire
Vector operator~(Vector const& v); // Retourne le vecteur unitaire
Vector operator-(Vector const& v); // Retourne le vecteur opposé
Vector operator+(Vector u, Vector const& v); // Addition
Vector operator-(Vector u, Vector const& v); // Soustraction
Vector operator^(Vector const& u, Vector const& v); // Produit vectoriel
double operator*(Vector const& u, Vector const& v); // Produit scalaire
bool operator==(Vector const& u, Vector const& v); // Operateur d'egalite
bool operator!=(Vector const& u, Vector const& v); 


