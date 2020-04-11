#include "math.h"
#include "top.h"
#include "constants.h"

// Constructeur d'un cone simple
SimpleCone::SimpleCone(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double rho, double L, double R, const char* add)
	: NonRollingTop(std::move(v), A, P, DP, add), rho(rho), L(L), R(R)
{
	m = 1.0/3.0 * M_PI * rho * pow(R, 2) * L; // masse
	d = 0.75 * L; // distance du CM du point de contact
	I_A1 = (3 * m) / 20.0 * (pow(R, 2) + 0.25 * pow(L, 2)); // axe horizontal
	I_A1 += m * pow(d, 2); // loi du transfert
	I_A3 = (3 * m) / 10.0 * pow(R, 2); // axe vertical
}

// Constructeur du Gyroscope
Gyroscope::Gyroscope(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double d, double rho, double L, double R, const char* add)
	: NonRollingTop(std::move(v), A, P, DP, add), rho(rho), L(L), R(R)
{
	this->d = d; // distance du CM du point de contact
	m = M_PI * pow(R, 2) * L * rho; // masse
	I_A1 = 0.25 * m * pow(R, 2); // axe horizontal
	I_A1 += m * pow(d, 2); // loi du transfert
	I_A3 =  0.5 * m * pow(R, 2); // axe vertical
}

// Methode d'affichage du cone
std::ostream& SimpleCone::print(std::ostream& os) const {
	return os << "Conique simple" << std::endl
		<< "paramètre : " << getP() << std::endl
		<< "dérivée   : " << getDP() << std::endl
		<< "masse volumique (kg m-3) : " << getDensity() << std::endl
		<< "hauteur (m) : " << getHeight() << std::endl
		<< "rayon   (m) : " << getRadius() << std::endl
		<< "origine (A) : " << getOrigin() << std::endl;
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

// Operateur d'affichage de la toupie
std::ostream &operator<<(std::ostream& os, Top const& a) {
	return a.print(os);
}

// Equation du mouvement d'une toupie sans roulement
// c.f. complement mathematique page 12 eq. 13-15
Vector NonRollingTop::getDDP(Vector P, Vector DP) const {
	using namespace constants;

	double cos_theta(cos(P[1]));
	double sin_theta(sin(P[1]));

	double d_psi(DP[0]);
	double d_theta(DP[1]);
	double d_phi(DP[2]);

	double d2_psi((I_A3 - 2*I_A1) * d_psi * cos_theta);
	d2_psi += I_A3 * d_phi;
	d2_psi *= d_theta / (I_A1 * sin_theta);

	double d2_theta((I_A1 - I_A3) * d_psi * cos_theta);
	d2_theta -= I_A3 * d_phi;
	d2_theta *= d_psi;
	d2_theta += m * g * d;
	d2_theta *= (1.0 / I_A1) * sin_theta;
	
	double d2_phi( I_A1 - (I_A3 - I_A1) * pow(cos_theta, 2) );
	d2_phi *= d_psi;
	d2_phi -= I_A3 * d_phi * cos_theta;
	d2_phi *= d_theta / (I_A1 * sin_theta);

	return Vector {d2_psi, d2_theta, d2_phi};
}
