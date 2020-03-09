#pragma once

#include <array>
#include "vect.h"

class Matrix3x3 {
	public:
		// Constructeur de la matrice identite
		Matrix3x3() {
			for (std::size_t i(0); i < 3; ++i) {
				for (std::size_t j(0); j < 3; ++j) {
					data_[i][j] = (i == j) ? 1.0 : 0.0;
				}
			}
		}
		Matrix3x3(std::array<std::array<double, 3>, 3> const& data)
		: data_(data)
		{}

		// Constructeur de la matrice composee d'un seul double
		Matrix3x3(double d){
			for (std::size_t i(0); i < 3; ++i) {
				for (std::size_t j(0); j < 3; ++j) {
					data_[i][j] = 0;
				}
			}
		}


		std::array<double, 3> operator[](std::size_t i) const { return data_[i]; }
		std::array<double, 3>& operator[](std::size_t i){ return data_[i]; }

		Matrix3x3 transp() const;
		double det() const;
		Matrix3x3 inv() const;

		Matrix3x3& swapLines(std::size_t l1, std::size_t l2);
		Matrix3x3& multLine(std::size_t l, double scal);
		Matrix3x3& addLine(std::size_t dst, std::size_t src, double scal);
	private:

		std::array<std::array<double, 3>, 3> data_;
};

Matrix3x3 operator+(Matrix3x3 const& A, Matrix3x3 const& B);
Matrix3x3 operator-(Matrix3x3 const& A, Matrix3x3 const& B);
Matrix3x3 operator*(Matrix3x3 const& A, Matrix3x3 const& B);

Matrix3x3 operator*(double d, Matrix3x3 const& A);
Vector operator*(Matrix3x3 const& A, Vector v);

bool operator==(Matrix3x3 const& A, Matrix3x3 const& B);
std::ostream &operator<<(std::ostream& os, Matrix3x3 const& A);
