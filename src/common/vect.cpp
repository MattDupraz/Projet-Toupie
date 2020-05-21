#include <iostream>
#include <cmath>

#include "vect.h"
#include "math_utils.h"

// Accesseurs
double Vector::operator[](std::size_t i) const {
	if (i >= size()) throw VECTOR_INDEX_OUT_OF_BOUNDS;
	return coords_[i];
}
double& Vector::operator[](std::size_t i) {
	if (i >= size()) throw VECTOR_INDEX_OUT_OF_BOUNDS;
	return coords_[i];
}

// Operateurs d'assignment
Vector& Vector::operator*=(double d) {
	for (std::size_t i(0); i < size(); ++i){
		coords_[i] *= d;
	}
	return *this;
}

// Additionne (modifie) a un vecteur un autre vecteur
Vector& Vector::operator+=(Vector const& other) {
	if (size() != other.size())
		throw INCOMPATIBLE_VECTOR_SIZE;
	for (size_t i(0); i < size(); i++){
		coords_[i] += other[i];
	}
	return *this;
}

// Soustrait (modifie) a un vecteur un autre vecteur
Vector& Vector::operator-=(Vector const& other) {
	if (size() != other.size())
		throw INCOMPATIBLE_VECTOR_SIZE;
	for (size_t i(0); i < size(); i++){
		coords_[i] -= other[i];
	}
	return *this;
}

// Ajoute une coordonnee au vecteur
Vector& Vector::augment(double val){
	coords_.push_back(val);
	return *this;
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

// Vecteur unitaire avec la meme direction
Vector operator~(Vector const& v) {
	return v * (1.0 / v.norm());
}

// Vecteur oppose
Vector operator-(Vector const& v) {
	return v * (-1.0);
}

// Produit vectoriel
Vector operator^(Vector const& u, Vector const& v) {
	if (u.size() != 3 || v.size() != 3) {
		throw INCOMPATIBLE_VECTOR_SIZE;
	}
	Vector result(std::size_t(3));
	result[0] = u[1]*v[2] - u[2]*v[1];
	result[1] = u[2]*v[0] - u[0]*v[2];
	result[2] = u[0]*v[1] - u[1]*v[0];
	return result;

}

// Produit scalaire
double operator*(Vector const& u, Vector const& v) {
	if (u.size() != v.size())
		throw INCOMPATIBLE_VECTOR_SIZE;
	double result(0);
	for (std::size_t i(0); i < u.size(); ++i){
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
			if (!isEqual(u[i], v[i])){
				return false;
			}
		}
	}
	return true;
}

// Multiplication par un scalaire a gauche
Vector operator*(double d, Vector v) {
	return v * d;
}

// Multiplication par un scalaire a droite
Vector operator*(Vector v, double d) {
	v *= d;
	return v;
}

// Addition des vecteurs
Vector operator+(Vector u, Vector const& v) {
	u += v;
	return u;
}

// Soustraction des vecteurs
Vector operator-(Vector u, Vector const& v) {
	u -= v;
	return u;
}

// Operateur d'egalite
bool operator!=(Vector const& u, Vector const& v) {
	return !(u == v);
}

// Gere les streams -> cout << vect; affiche le vecteur
std::ostream &operator<<(std::ostream& os, Vector const& v) {
	for (std::size_t i(0); i < v.size(); ++i) {
		if (i != 0) {
			os << " ";
		}
		os << v[i];
	}
	return os;
}






