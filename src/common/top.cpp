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

Vector Top::getPosCM() const {
	Vector relative({0, getHeightCM(), 0});
	relative = getOrientationMatrix() * relative;
	return getContactPoint() + relative; 
}

Vector Top::getVelocityCM() const {
	
}

Matrix3x3 Top::getInertiaMatrix() const {
	return Matrix3x3({
		{getI_xy(),0,0},
		{0,getI_xy(),0},
		{0,0,getI_z()}
	});
}
Matrix3x3 Top::getOrientationMatrix() const {
	double cos_theta(cos(theta()));
	double sin_theta(sin(theta()));
	double cos_psi(cos(psi()));
	double sin_psi(sin(psi()));
	Matrix3x3 S1({
		{1,0,0},
		{0,cos_theta,sin_theta},
		{0,-sin_theta,cos_theta}
	});
	Matrix3x3 S2({
		{cos_psi,sin_psi,0},
		{-sin_psi,cos_psi,0},
		{0,0,1}
	});
	return Matrix3x3(S1*S2);
}

