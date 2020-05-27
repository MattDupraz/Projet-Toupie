#include "top_simple_cone.h"
#include "math.h"

// Constructeur d'un cone simple
SimpleCone::SimpleCone(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double rho, double L, double R)
	: NonRollingTop(std::move(v), A, P, DP), rho(rho), L(L), R(R)
{
	// c.f. complément page 8
	m = 1.0/3.0 * M_PI * rho * pow(R, 2) * L; // masse
	d = 0.75 * L; // distance du CM du point de contact
	I_1 = (3 * m) / 20.0 * (pow(R, 2) + 0.25 * pow(L, 2)); // axe horizontal
	I_3 = (3 * m) / 10.0 * pow(R, 2); // axe vertical
}

// Methode d'affichage du cone
std::ostream& SimpleCone::print(std::ostream& os) const {
	return os << "Conique simple" << std::endl
		<< "paramètre : " << getP() << std::endl
		<< "dérivée   : " << getDP() << std::endl
		<< "masse volumique (kg m-3) : " << getDensity() << std::endl
		<< "hauteur (m) : " << getHeight() << std::endl
		<< "rayon   (m) : " << getRadius() << std::endl
		<< "origine (A) : " << getOrigin() << std::endl
		<< "masse : " << getMass() << std:: endl;
}
