#include <utility>

#include "matrix_3x3.h"
#include "math_utils.h"

// Constructeur d'une matrice scalaire
Matrix3x3::Matrix3x3(double val) {
	for (std::size_t i(0); i < 3; ++i) {
		for (std::size_t j(0); j < 3; ++j) {
			data_[i][j] = (i == j) ? val : 0.0;
		}
	}
}
// Constructeur prenant un tableau 3x3
Matrix3x3::Matrix3x3(double (&&data)[3][3]) {
	for (std::size_t i(0); i < 3; ++i) {
		for (std::size_t j(0); j < 3; ++j) {
			data_[i][j] = data[i][j];
		}
	}
}
// Constructeur pour eviter l'initialisation inutile
// d'une matrice identite, s'il y en a pas besoin
Matrix3x3::Matrix3x3(DoubleArray3x3& data)
	: data_(std::move(data))
{}

// Retourne la transposée
Matrix3x3 Matrix3x3::transp() const{
	Matrix3x3 result(*this);	
	for (std::size_t i(0); i < 3; ++i) {
		for (std::size_t j(0); j < i; ++j) {
			std::swap(result[i][j], result[j][i]);
		}
	}
	return result;
}

// Retourne le mineur
double Matrix3x3::getMinor(std::size_t row, std::size_t col) const {
	// On trouve les indices pour la sous-matrice 2x2
	std::size_t i1((row == 0) ? 1 : 0);
	std::size_t i2((row == 2) ? 1 : 2);
	std::size_t j1((col == 0) ? 1 : 0);
	std::size_t j2((col == 2) ? 1 : 2);
	// On retourne son determinant
	return data_[i1][j1]*data_[i2][j2] - data_[i1][j2]*data_[i2][j1];
}

// Retourne le cofacteur
double Matrix3x3::cofactor(std::size_t row, std::size_t col) const {
	return ((row + col) % 2 == 0) ? getMinor(row, col) : -getMinor(row, col);
}

// Retourne la matrice des cofacteurs
Matrix3x3 Matrix3x3::cofactorMatrix() const {
	// On cree un array au lieu d'initialiser une matrice
	// pour eviter l'overhead de la creation de la matrice identite
	DoubleArray3x3 arr;
	for (std::size_t i(0); i < 3; ++i) {
		for (std::size_t j(0); j < 3; ++j) {
			arr[i][j] = cofactor(i, j);
		}
	}
	return Matrix3x3(arr);
}

// Retourne le determinant de la matrice
double Matrix3x3::det() const {
	double det(0);
	// On utilise la regle de Sarrus pour calculer le determinant
	for (std::size_t i(0); i < 3 ;++i) {
		det += data_[i][0] * data_[(i+1)%3][1] * data_[(i+2)%3][2];
		det -= data_[(i+2)%3][0] * data_[(i+1)%3][1] * data_[i][2];
	}
	return det;
}

// Retourne l'inverse de la matrice
Matrix3x3 Matrix3x3::inv() const {
	double determinant(det());
	if (math::isEqual(determinant, 0.0)) {
		throw NOT_INVERSIBLE;
	}
	return (1.0 / determinant) * cofactorMatrix().transp();
}

// Echange de deux lignes (operation elementaire)
Matrix3x3& Matrix3x3::swapLines(std::size_t l1, std::size_t l2){
	std::swap(data_[l1], data_[l2]);
	return *this;
}

// Multiplication d'une ligne par un scalaire (operation elementaire)
Matrix3x3&  Matrix3x3::multLine(std::size_t l, double scal){
	for (double& val : data_[l]){
		val *= scal;
	}
	return *this;
}

// Addition d'une ligne `scal` fois a une autre (operation elementaire)
Matrix3x3&  Matrix3x3::addLine(std::size_t dst, std::size_t src, double scal){
	for (std::size_t i(0) ; i < 3 ; ++i){
		data_[dst][i] += scal*data_[src][i];
	}
	return *this;
}

////////////////////////////////////////////////////
// OPERATIONS USUELLES SUR L'ALGEBRE DES MATRICES //
////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator+=(Matrix3x3 const& other) {
	for (std::size_t i(0); i < 3; ++i){
		for (std::size_t j(0); j < 3; ++j){
			data_[i][j] += other[i][j];
		}
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator-=(Matrix3x3 const& other) {
	for (std::size_t i(0); i < 3; ++i){
		for (std::size_t j(0); j < 3; ++j){
			data_[i][j] -= other[i][j];
		}
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator*=(double scal) {
	for (std::size_t i(0); i < 3; ++i){
		for (std::size_t j(0); j < 3; ++j){
			data_[i][j] *= scal;
		}
	}
	return *this;	
}

Matrix3x3 operator+(Matrix3x3 A, Matrix3x3 const& B){
	A += B;
	return A;
}

Matrix3x3 operator-(Matrix3x3 A, Matrix3x3 const& B){
	A -= B;
	return B;
}

Matrix3x3 operator*(Matrix3x3 const& A, Matrix3x3 const& B){
	Matrix3x3 M(0);
	for (std::size_t i(0); i < 3; ++i){
		for (std::size_t j(0); j < 3; ++j){
			for (std::size_t k(0); k < 3 ; ++k){
				M[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return M;
}

Matrix3x3 operator*(double d, Matrix3x3 A){
	A *= d;	
	return A;
}

Vector operator*(Matrix3x3 const& A, Vector const& v){
	Vector w(std::size_t(3));
	for (std::size_t i(0); i < 3 ; ++i){
		for (std::size_t j(0); j < 3 ; ++j){
			w[i] += A[i][j] * v[j];
		}
	}
	return w;
}

bool operator==(Matrix3x3 const& A, Matrix3x3 const& B){
	for (std::size_t i(0); i < 3 ; ++i){
		for (std::size_t j(0); j < 3 ; ++j){
			if (!math::isEqual(A[i][j], B[i][j])){
				return false;
			}
		}
	}
	return true;
}

bool operator !=(Matrix3x3 const& A, Matrix3x3 const& B){
	return !(A == B);
}

// Affiche la matrice dans un flot
// (sur multiples lignes, avec un arret de ligne a apres la matrice)
std::ostream& operator<<(std::ostream& os, Matrix3x3 const& A){
	os.precision(2);
	os << std::fixed;
	for (std::size_t i(0); i < 3 ; ++i){
		os << (i == 0 ? "[[" : " [");
		for (std::size_t j(0); j < 3 ; ++j){
			os.width(7);
			double val(A[i][j]);
			// Check pour eviter d'imprimmer des 0 negatifs
			os << (math::isEqual(val, 0.0) ? 0 : val);
			if (j != 2) 
				os << " ";
		}
		os << (i == 2 ? "]]" : "]") << std::endl;
	}
	os.unsetf(std::ios_base::floatfield);

	return os;
}
