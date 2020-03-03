#include <cmath>
#include <iostream>

#include "vect.h"


// Retourne le vecteur unitaire avec la meme direction
Vector operator~(Vector const& v) {
	return v * (1.0 / v.norm());
}

// Retourne le vecteur oppose
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

Vector operator+(Vector const& u, Vector const& v) {

}

Vector operator-(Vector const& u, Vector const& v) {

}

Vector operator^(Vector const& u, Vector const& v) {

}

double operator*(Vector const& u, Vector const& v) {

}

bool operator==(Vector const& u, Vector const& v) {

}

// Additionne deux vecteurs
Vector Vector::operator+(Vector const& other) const {
	if (other.size() > size()) {
		return other + *this;
	}
	Vector result(*this);	
	for (size_t i(0); i < std::min(size(), other.size()); i++){
		result.set(i, get(i) + other.get(i));
	}
	return result;
}

// Produit vectoriel
Vector Vector::operator^(Vector const& other) const {
	if (size() != 3 || other.size() != 3) {
		return Vector(); // a reconsiderer...
	}
	Vector result(*this);
	result[0] = (*this)[1] * other.get(2) - get(2)*other.get(1);
	result.set(1, get(2)*other.get(0) - get(0)*other.get(2));
	result.set(2, get(0)*other.get(1) - get(1)*other.get(0));
	return result;
}

// Produit scalaire
double Vector::operator*(Vector const& other) const {
	double result(0);
	for (std::size_t i(0); i < std::min(size(), other.size()); ++i){
		result += get(i) * other.get(i);
	}
	return result;
}

// Soustrait deux vecteurs
Vector Vector::operator-(Vector const& other) const {
	return *this + (-other);
}

// Verifie l'egalite de deux vecteurs
bool Vector::operator==(Vector const& other) const {
	if (size() != other.size()) {
		return false;
	} else {
		for (std::size_t i(0); i < size(); ++i){
			if (!(std::abs(other.get(i) - get(i)) < 1e-10)){
				return false;
			}
		}
	}
	return true;
}

// Multiplie un vecteur par un scalaire
Vector Vector::operator*(double scalar) const {
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





