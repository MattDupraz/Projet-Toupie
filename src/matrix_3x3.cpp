#include "matrix_3x3.h"
#include <algorithm>
#include <iostream>

//  Retourne la transposee

Matrix3x3 Matrix3x3::transp() const{
	Matrix3x3 M(*this);
	
	for (size_t i(0); i < 3; ++i) {
		for (size_t j(0); j < i; ++j) {
			std::swap(M[i][j], M[j][i]);
		}
	}
	return M;
}

double Matrix3x3::det() const{
	double det(0);
	Matrix3x3 const& M(*this);
	for (size_t i(0); i < 3 ; ++i) {
		
		det += M[i][0] * M[(i+1)%3][1] * M[(i+2)%3][2];
		
		det -= M[(i+2)%3][0] * M[(i+1)%3][1] * M[i][2];
	}
	return det;
}

Matrix3x3& Matrix3x3::swapLines(std::size_t l1, std::size_t l2){
	std::swap( data_[l1] , data_[l2] );
	return *this;
}

Matrix3x3&  Matrix3x3::multLine(std::size_t l, double scal){
	for (auto& num : data_[l]){
		num *= scal;
	}
	return *this;
}

Matrix3x3&  Matrix3x3::addLine(std::size_t dst, std::size_t src, double scal){
	for (size_t i(0) ; i < 3 ; ++i){
		data_[dst][i] += scal*data_[src][i];
	}
	return *this;
}

std::ostream &operator<<(std::ostream& os, Matrix3x3 const& A){
	for (size_t i(0); i < 3 ; ++i){
		for (size_t j(0); j < 3 ; ++j){
			std::cout << A[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	return os;
}



Matrix3x3 Matrix3X3::inv(){
	int i(0);
	while ()
	
}



int main(){
	Matrix3x3 M;
	std::cout << M;
	M.addLine(0,1,1);
	M.addLine(0,2,1);
	M.multLine(0,12.4);
	std::cout << M;
	
	return 0;
}

