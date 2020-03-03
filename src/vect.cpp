#include <cmath>
#include <iostream>

#include "vect.h"

// Vecteur unitaire avec la meme direction
Vector operator~(Vector const& v) {
	return v * (1.0 / v.norm());
}

// Vecteur oppose
Vector operator-(Vector const& v) {
	Vector result;
	for (std::size_t i(0); i < v.size(); ++i){
		result.augment(-v[i]);
	}
	return result;
}

// Multiplication par un scalaire a gauche
Vector operator*(double d, Vector const& v) {
	return v * d;
}

// Multiplication par un scalaire a droite
Vector operator*(Vector const& v, double d) {
	Vector result;
	for (std::size_t i(0); i < v.size(); ++i){
		result.augment(d * v[i]);
	}
	return result;

}

// Addition des vecteurs
Vector operator+(Vector const& u, Vector const& v) {
	Vector result((u.size() > v.size()) ? u : v);	
	for (size_t i(0); i < std::min(u.size(), v.size()); i++){
		result[i] = u[i] + v[i];
	}
	return result;
}

// Soustraction des vecteurs
Vector operator-(Vector const& u, Vector const& v) {
	return u + (-v);
}

// Produit vectoriel
Vector operator^(Vector const& u, Vector const& v) {
	Vector result(std::size_t(3));
	if (u.size() != 3 || v.size() != 3) {
		return result; // == vecteur nul; a reconsiderer
	}
	result[0] = u[1]*v[2] - u[2]*v[1];
	result[1] = u[2]*v[0] - u[0]*v[2];
	result[2] = u[0]*v[1] - u[1]*v[0];
	return result;

}

// Produit scalaire
double operator*(Vector const& u, Vector const& v) {
	double result(0);
	for (std::size_t i(0); i < std::min(u.size(), v.size()); ++i){
		result += u[i] * v[i];
	}
	return result;
}

// Verifie l'egalite de deux vecteurs
bool operator==(Vector const& u, Vector const& v) {
	if (u.size() != v.size()) {
		return false;
	} else {
		for (std::size_t i(0); i < u.size(); ++i){
			if (!(std::abs(u[i] - v[i]) < 1e-10)){
				return false;
			}
		}
	}
	return true;
}

// Gere les streams -> cout << vect; affiche le vecteur
std::ostream &operator<<(std::ostream& os, Vector const& v) {
	os << "(";
	for (std::size_t i(0); i < v.size(); ++i) {
		if (i != 0) {
			os << ", ";
		}
		os << v[i];
	}
	return os << ")";
}

// Ajoute une coordonnee au vecteur
void Vector::augment(double val){
	coords_.push_back(val);
}

// Retourne la norme du vecteur
double Vector::norm() const {
	return std::sqrt(norm2());
}

// Retourne la norme du vecteur au carre		
double Vector::norm2() const {
	double result(0);
	for (double d : coords_){
		result += d*d;
	}
	return result;
}





