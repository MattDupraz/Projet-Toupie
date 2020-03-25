#include "math.h"
#include "top.h"
#include "constants.h"

// Initialisation d'un cone simple
SimpleCone::SimpleCone(View* v, Vector const& P, Vector const& DP,
		double rho, double L, double R)
	: Gyroscope( v, P, DP )
{
	m = 1.0/3.0 * M_PI * rho * pow(R, 2) * L;
	d = 0.75 * L;
	I_A1 = (3 * m) / 20.0 * (pow(R, 2) + 0.25 * pow(L, 2));
	I_A1 += m * pow(d, 2);
	I_A3 = (3 * m) / 10.0 * pow(R, 2);
}

// Voir complement mathematique page 12 eq. 13-15
Vector Gyroscope::getDDP() const {
	using namespace constants;

	double cos_theta(cos(theta()));
	double sin_theta(sin(theta()));

	double d2_psi((I_A3 - 2*I_A1) * d_psi() * cos_theta);
	d2_psi += I_A3 * d_phi();
	d2_psi *= d_theta() / (I_A1 * sin_theta);

	double d2_theta((I_A1 - I_A3) * d_psi() * cos_theta);
	d2_theta -= I_A3 * d_phi();
	d2_theta *= d_psi();
	d2_theta += m * g * d;
	d2_theta *= (1.0 / I_A1) * sin_theta;
	
	double d2_phi( I_A1 - (I_A3 - I_A1) * pow(cos_theta, 2) );
	d2_phi *= d_psi();
	d2_phi -= I_A3 * d_phi() * cos_theta;
	d2_phi *= d_theta() / (I_A1 * sin_theta);

	return Vector {d2_psi, d2_theta, d2_phi};
}

/*
void ConeSimple::init_tendor(double length, double radius){
	double r(radius*radius);
	double l(length*length);
	
	tensorInert_= {{mass_*(3/20*r+3/5*l),0,0},{0,0,0},{0,0,3*mass_*(r/10 +3*l/16)}};
}*/
