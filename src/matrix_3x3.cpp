#include "matrix_3x3.h"
#include <algorithm>
#include <iostream>

//  Retourne la transposee

Matrix3x3 Matrix3x3::transp() const{
	Matrix3x3 result(*this);
	
	for (std::size_t i(0); i < 3; ++i) {
		for (std::size_t j(0); j < i; ++j) {
			std::swap(result[i][j], result[j][i]);
		}
	}
	return result;
}

double Matrix3x3::det() const{
	double det(0);
	for (std::size_t i(0); i < 3 ; ++i) {
		
		det += data_[i][0] * data_[(i+1)%3][1] * data_[(i+2)%3][2];
		
		det -= data_[(i+2)%3][0] * data_[(i+1)%3][1] * data_[i][2];
	}
	return det;
}

Matrix3x3& Matrix3x3::swapLines(std::size_t l1, std::size_t l2){
	std::swap(data_[l1], data_[l2]);
	return *this;
}

Matrix3x3&  Matrix3x3::multLine(std::size_t l, double scal){
	for (double& val : data_[l]){
		val *= scal;
	}
	return *this;
}

Matrix3x3&  Matrix3x3::addLine(std::size_t dst, std::size_t src, double scal){
	for (std::size_t i(0) ; i < 3 ; ++i){
		data_[dst][i] += scal*data_[src][i];
	}
	return *this;
}

std::ostream &operator<<(std::ostream& os, Matrix3x3 const& A){
	for (std::size_t i(0); i < 3 ; ++i){
		for (std::size_t j(0); j < 3 ; ++j){
			std::cout << A[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	return os;
}

Matrix3x3 Matrix3x3::inv() const {
	Matrix3x3 mat(*this);
	Matrix3x3 result;
	for (std::size_t i(0); i < 3; ++i) {
		// Il faut mettre une valeur non-nulle sur l'echelon
		if (std::abs(mat[i][i]) < 1e-10) {
			bool success(false);
			for (std::size_t j(i + 1); i < 3 && !success; ++i) {
				if (std::abs(mat[j][i]) > 1e-10) {
					mat.swapLines(i, j);
					result.swapLines(i, j);
					success = true;
				}
			}
			// if !success throw EXCEPTION
		}

		// On multiplie la ligne pour assurer que la valeur de l'echelon c'est 1
		double val(1.0/mat[i][i]);
		mat.multLine(i, val);
		result.multLine(i, val);

		// On annule toutes les autres valeurs dans la colonne
		for (std::size_t j(0); j < 3; ++j) {
			if (j != i && std::abs(mat[j][i]) > 1e-10) {
				val = mat[j][i];
				mat.addLine(j, i, -val);
				result.addLine(j, i, -val);
			}
		}
	}
	return result;
}



int main(){
	Matrix3x3 M;
	std::cout << M;
	M.addLine(2, 0, 0.2);
	M.addLine(1, 0, 4.1);
	M.addLine(0,1,2.1);
	M.addLine(0,2,3.8);
	M.addLine(2,1,0.4);
	M.multLine(0,12.4);
	M.addLine(1,2,3.1);
	M.addLine(0,1,-2.3);
	std::cout << M;
	std::cout << M.inv();
	
	return 0;
}

