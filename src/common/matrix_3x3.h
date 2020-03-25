#pragma once

#include <array>
#include <ostream>

#include "vect.h"

enum MatrixException { NOT_INVERSIBLE };

typedef std::array<std::array<double, 3>, 3> DoubleArray3x3;

class Matrix3x3 {
	public:
		// Constructeur d'une  matrice scalaire
		Matrix3x3(double val = 1.0);
		// Constructeur permettant d'intialiser a partir d'un array in-line
		// e.g.: Matrix3x3 M({{1, 2, 3}, {1, 2, 3}, {1, 2, 3}});
		Matrix3x3(double (&&data)[3][3]);
		// Constructeur pour eviter l'initialisation inutile
		// d'une matrice identite, s'il y en a pas besoin
		Matrix3x3(DoubleArray3x3& data);

		// Accesseurs [] s'utilisent de la meme maniere que si Matrix3x3 etait de type double[][3]
		std::array<double, 3> operator[](std::size_t i) const { return data_[i]; }
		std::array<double, 3>& operator[](std::size_t i){ return data_[i]; }

		// Operations usuelles sur l'algebre des matrices
		Matrix3x3& operator+=(Matrix3x3 const&);
		Matrix3x3& operator-=(Matrix3x3 const&);
		Matrix3x3& operator*=(double);

		// Notions algebriques pour les matrices 
		Matrix3x3 transp() const;
		double det() const;
		Matrix3x3 inv() const;
		double getMinor(std::size_t i, std::size_t j) const;
		double cofactor(std::size_t i, std::size_t j) const;
		Matrix3x3 cofactorMatrix() const;

		// Operations elementaires sur les matrices
		Matrix3x3& swapLines(std::size_t l1, std::size_t l2);
		Matrix3x3& multLine(std::size_t l, double scal);
		Matrix3x3& addLine(std::size_t dst, std::size_t src, double scal);
	private:	
		DoubleArray3x3 data_;
};

// Operator overloads pour les operations usuelles sur l'algebre des matrices
Matrix3x3 operator+(Matrix3x3 A, Matrix3x3 const& B);
Matrix3x3 operator-(Matrix3x3 A, Matrix3x3 const& B);
Matrix3x3 operator*(Matrix3x3 const& A, Matrix3x3 const& B);
Matrix3x3 operator*(double d, Matrix3x3 A);
Vector operator*(Matrix3x3 const& A, Vector const& v);
bool operator==(Matrix3x3 const& A, Matrix3x3 const& B);
bool operator!=(Matrix3x3 const& A, Matrix3x3 const& B);
std::ostream& operator<<(std::ostream& os, Matrix3x3 const& A);
