#include <iostream>
#include <cmath>

#include "vect.h"

// Retourne le vecteur oppose
Vector Vector::operator-() const {
	Vector result;
	for (std::size_t i(0); i < size(); ++i){
		result.augment(-get(i));
	}
	return result;
}

// Additionne deux vecteurs
Vector Vector::operator+(Vector const& other) const {
	Vector result(*this);	
	for (size_t i(0); i < std::min(size(), other.size()); i++){
		result.set(i, get(i) + other.get(i));
	}
	return result;
}

// Produit vectoriel
Vector Vector::operator^(Vector const& other) const {
	Vector result(*this);
	//ATTENTION LES VECTEURS NE SONT PAS FORCEMENT 3D
	//A REVOIR
	result.set(0, get(1)*other.get(2) - get(2)*other.get(1));
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
	Vector result(*this);
	for (std::size_t i(0); i < size(); ++i){
		result.set(i, scalar * get(i));
	}
	return result;
}

// Ajoute une coordonnee au vecteur
void Vector::augment(double val){
	coords_.push_back(val);
}

// Fonction afficher le vecteur
void Vector::print() const {
	for (double c : coords_) {
		std::cout << c << "  ";
	}
	std::cout << std::endl;
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


// Retourne le vecteur unitaire avec la meme direction
Vector Vector::unitVector() const {
	return (*this) * (1.0 / norm());
}
