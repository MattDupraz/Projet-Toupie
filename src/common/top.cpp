#include "math.h"
#include "top.h"
#include "constants.h"

// Operateur d'affichage de la toupie
std::ostream &operator<<(std::ostream& os, Top const& a) {
	return a.print(os);
}

Vector Top::getAngVelocity() const {
	return Vector({d_theta(), d_psi() * sin(theta()), 
			d_psi() * cos(theta()) + d_phi()});
}

Vector Top::getPosA() const {
	return Vector({x(), y(), z()});
}

Vector Top::getPosG() const {
	return getPosA() + getAG(); 
}

Vector Top::getVelocityA() const {
	return Vector({dx(), dy(), dz()});
}

Vector Top::getVelocityG() const {
	Vector v_A(getVelocityA());
	Vector omega(getOrientationMatrix() * getAngVelocity());
	Vector v_G(v_A + omega ^ getAG());
	return v_G;
}

Vector Top::getAngMomentumA() const {
	return getInertiaMatrixA() * getAngVelocity();
}

Vector Top::getAngMomentumG() const {
	return getInertiaMatrixG() * getAngVelocity();
}

double Top::getEnergy() const {
	double E_c(0.5 * (getMass() * getVelocityG().norm2()
			+ getAngMomentumG() * getAngVelocity()));
	Vector g({0, 0, -constants::g});
	double E_g(-getMass() * g * getPosG());
	return E_c+E_g;
}

double Top::getMomentInertiaA_xy() const {
	return getMomentInertia_xy() + getMass() * getAG().norm2();
}

double Top::getProduitMixte()const{
	return (getAngVelocity()^getAngMomentumG())[2];
}

Matrix3x3 Top::getInertiaMatrixG() const {
	return Matrix3x3({
		{getMomentInertia_xy(),0,0},
		{0,getMomentInertia_xy(),0},
		{0,0,getMomentInertia_z()}
	});
}

Matrix3x3 Top::getInertiaMatrixA() const {
	return Matrix3x3({
		{getMomentInertiaA_xy(),0,0},
		{0,getMomentInertiaA_xy(),0},
		{0,0,getMomentInertia_z()}
	});
}

Matrix3x3 Top::getOrientationMatrix() const {
	double cos_theta(cos(theta()));
	double sin_theta(sin(theta()));
	double cos_psi(cos(psi()));
	double sin_psi(sin(psi()));
	Matrix3x3 rot_z({
		{cos_psi,-sin_psi,0},
		{sin_psi,cos_psi,0},
		{0,0,1}
	});
	Matrix3x3 rot_x({
		{1,0,0},
		{0,cos_theta,-sin_theta},
		{0,sin_theta,cos_theta}
	});
	return Matrix3x3(rot_z*rot_x);
}
