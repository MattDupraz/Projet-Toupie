#include "top_gyroscope.h"

// Constructeur du Gyroscope
Gyroscope::Gyroscope(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double d, double rho, double L, double R)
	: NonRollingTop(std::move(v), A, P, DP), rho(rho), L(L), R(R)
{
	this->d = d; // distance du CM du point de contact
	m = M_PI * pow(R, 2) * L * rho; // masse
	I_A1 = 0.25 * m * pow(R, 2); // axe horizontal
	I_A1 += m * pow(d, 2); // loi du transfert
	I_A3 =  0.5 * m * pow(R, 2); // axe vertical
}

// Methode d'affichage du gyroscope
std::ostream& Gyroscope::print(std::ostream& os) const {
	return os << "Gyroscope" << std::endl
		<< "paramètre : " << getP() << std::endl
		<< "dérivée   : " << getDP() << std::endl
		<< "masse volumique (kg m-3) : " << getDensity() << std::endl
		<< "largeur (m) : " << getThickness() << std::endl
		<< "rayon   (m) : " << getRadius() << std::endl
		<< "origine (A) : " << getOrigin() << std::endl
		<< "distance du sol (m) : " << getHeight() << std::endl;
}
