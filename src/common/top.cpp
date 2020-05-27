#include "math.h"
#include "top.h"
#include "constants.h"

// Operateur d'affichage de la toupie
std::ostream &operator<<(std::ostream& os, Top const& a) {
	return a.print(os);
}

// Vitesse angulaire
Vector Top::getAngVelocity() const {
	// Dans le repère de la toupie
	return Vector({d_theta(), d_psi() * sin(theta()), 
			d_psi() * cos(theta()) + d_phi()});
}

// Position du point de contact
Vector Top::getPosA() const {
	return Vector({x(), y(), z()});
}

// Position du centre de masse
Vector Top::getPosG() const {
	return getPosA() + getAG(); 
}

// Vitesse du point de contact
Vector Top::getVelocityA() const {
	return Vector({dx(), dy(), dz()});
}

// Vitesse du centre de masse
Vector Top::getVelocityG() const {
	Vector v_A(getVelocityA());
	Vector omega(getMatrixToGlobal() * getAngVelocity());
	Vector v_G(v_A + (omega ^ getAG()));
	return v_G;
}

// Moment cinétique par rapport à A
Vector Top::getAngMomentumA() const {
	// Dans le repère de la toupie
	return getInertiaMatrixA() * getAngVelocity();
}

// Moment cinétique par rapport à G
Vector Top::getAngMomentumG() const {
	// Dans le repère de la toupie
	return getInertiaMatrixG() * getAngVelocity();
}

// Énergie totale de la toupie
double Top::getEnergy() const {
	// Énergie cinétique
	double E_c(0.5 * (getMass() * getVelocityG().norm2()
			+ getAngMomentumG() * getAngVelocity()));
	Vector g({0, 0, -constants::g});
	// Énergie potentielle gravitationelle
	double E_g(-getMass() * g * getPosG());
	return E_c + E_g;
}

double Top::getMixedProduct() const {
	// Devrait être nul en géneral
	return (getAngVelocity()^getAngMomentumG())[2];
}

Matrix3x3 Top::getInertiaMatrixG() const {
	return Matrix3x3({
		{getMomentInertia_xy(),0,0},
		{0,getMomentInertia_xy(),0},
		{0,0,getMomentInertia_z()}
	});
}

// Matrice d'inertie en A
// Theorème d'Huygens-Steiner
Matrix3x3 Top::getInertiaMatrixA() const {
	Matrix3x3 I(getInertiaMatrixG());
	Vector AG(getMatrixFromGlobal()*getAG());
	double AGx(AG[0]), AGy(AG[1]), AGz(AG[2]);
	Matrix3x3 D({
			{AGy*AGy + AGz*AGz, -AGx*AGy, -AGx*AGz},
			{-AGy*AGx, AGx*AGx + AGz*AGz, -AGy*AGz},
			{-AGz*AGx, -AGz*AGy, AGx*AGx + AGy*AGy}
		});
	return I + getMass() * D;
}

// Matrice de passage du repère de la toupie au repère d'inertie
Matrix3x3 Top::getMatrixToGlobal() const {
	double cos_theta(cos(theta()));
	double sin_theta(sin(theta()));
	double cos_psi(cos(psi()));
	double sin_psi(sin(psi()));
	// Rotation +psi autour de l'axe z
	Matrix3x3 rot_z({
		{cos_psi,-sin_psi,0},
		{sin_psi,cos_psi,0},
		{0,0,1}
	});
	// Rotation +theta autour de l'axe x
	Matrix3x3 rot_x({
		{1,0,0},
		{0,cos_theta,-sin_theta},
		{0,sin_theta,cos_theta}
	});
	return Matrix3x3(rot_z*rot_x);
}

// Matrice de passage du repère de la toupie au repère d'inertie
Matrix3x3 Top::getMatrixFromGlobal() const {
	double cos_theta(cos(theta()));
	double sin_theta(sin(theta()));
	double cos_psi(cos(psi()));
	double sin_psi(sin(psi()));
	// Rotation -theta autour de l'axe x
	Matrix3x3 rot_x({
		{1,0,0},
		{0,cos_theta,sin_theta},
		{0,-sin_theta,cos_theta}
	});
	// Rotation -psi autour de l'axe z
	Matrix3x3 rot_z({
		{cos_psi,sin_psi,0},
		{-sin_psi,cos_psi,0},
		{0,0,1}
	});
	return Matrix3x3(rot_x*rot_z);
}
