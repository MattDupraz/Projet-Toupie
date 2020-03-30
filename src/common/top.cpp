#include "math.h"
#include "top.h"
#include "constants.h"

// Initialisation d'un cone simple
SimpleCone::SimpleCone(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double rho, double L, double R)
	: NonRollingTop(std::move(v), A, P, DP), rho(rho), L(L), R(R)
{
	m = 1.0/3.0 * M_PI * rho * pow(R, 2) * L;
	d = 0.75 * L;
	I_A1 = (3 * m) / 20.0 * (pow(R, 2) + 0.25 * pow(L, 2));
	I_A1 += m * pow(d, 2);
	I_A3 = (3 * m) / 10.0 * pow(R, 2);
}

Gyroscope::Gyroscope(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double d, double rho, double L, double R)
	: NonRollingTop(std::move(v), A, P, DP), rho(rho), L(L), R(R)
{
	this->d = d;
	m = M_PI * pow(R, 2) * L * rho;
	I_A1 = 0.25 * m * pow(R, 2);
	I_A1 += m * pow(d, 2);
	I_A3 =  0.5 * m * pow(R, 2);
}

std::ostream& SimpleCone::print(std::ostream& os) const {
	return os << "Conique simple" << std::endl
		<< "paramètre : " << getP() << std::endl
		<< "dérivée   : " << getDP() << std::endl
		<< "masse volumique (kg m-3) : " << getDensity() << std::endl
		<< "hauteur (m) : " << getHeight() << std::endl
		<< "rayon   (m) : " << getRadius() << std::endl
		<< "origine (A) : " << getOrigin() << std::endl;
}

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


std::ostream &operator<<(std::ostream& os, Top const& a) {
	return a.print(os);
}

// Voir complement mathematique page 12 eq. 13-15
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

/*
void ConeSimple::init_tendor(double length, double radius){
	double r(radius*radius);
	double l(length*length);
	
	tensorInert_= {{mass_*(3/20*r+3/5*l),0,0},{0,0,0},{0,0,3*mass_*(r/10 +3*l/16)}};
}*/
