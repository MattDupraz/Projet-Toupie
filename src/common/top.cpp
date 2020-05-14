#include "math.h"
#include "top.h"

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

Vector Top::getAG() const {
	Vector AG({0, getHeightCM(), 0});
	AG = getOrientationMatrix() * AG;
	return AG;
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

double Top::getI_Axy() const {
	return getI_z() + getMass() * pow(getHeightCM(), 2);
}

Matrix3x3 Top::getInertiaMatrix() const {
	return Matrix3x3({
		{getI_xy(),0,0},
		{0,getI_xy(),0},
		{0,0,getI_z()}
	});
}

Matrix3x3 Top::getInertiaMatrixA() const {
	return Matrix3x3({
		{getI_Axy(),0,0},
		{0,getI_Axy(),0},
		{0,0,getI_z()}
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



