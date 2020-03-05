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

		std::array<double, 3> operator[](std::size_t i) const { return data_[i]; }
		std::array<double, 3>& operator[](std::size_t i) { return data_[i]; }

		Matrix3x3 transp() const;
		double det() const;
		Matrix3x4 inv() const;
	private:
		std::array<std::array<double, 3>, 3> data_;
}

Matrix3x3 operator+(Matrix3x3 const& A, Matrix3x3 const& B);
Matrix3x3 operator-(Matrix3x3 const& A, Matrix3x3 const& B);
Matrix3x3 operator*(Matrix3x3 const& A, Matrix3x3 const& B);
Matrix3x3 operator*(double d, Matrix const& A);
Vector operator*(Matrix3x3 const& A, Vector v);

bool operator==(Matrix3x3 const& A, Matrix3x3 const& B);
std::ostream &operator<<(std::ostream& os, Matrix3x3 const& A);
