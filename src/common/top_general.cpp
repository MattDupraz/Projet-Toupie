#include "top_general.h"
#include "math.h"
#include "math_utils.h"
#include "constants.h"

GeneralTop::GeneralTop(std::shared_ptr<View> v,
			Vector const& P, Vector const& DP,
			double rho, Vector layers, double thickness)
	:Top(std::move(v), P, DP), rho(rho), layers(layers), L(thickness)
{
	// c.f. page 9 du complément
	
	// Initialise m
	for (size_t i(0); i < layers.size() ; ++i){
		m += M_PI*rho*L*layers[i]*layers[i];
	}

	// Initialise d
	double a(0);
	double b(0);
	for (size_t k(0); k < layers.size() ; ++k){
		double r2 = pow(layers[k], 2);
		a += r2;
		b += (2*k+1) * 0.5 * L * r2;	
	}	
	d = b/a;

	// Initialise I
	for (size_t i(0); i < layers.size(); ++i){
		I_3 += M_PI * 0.5 * rho * L * pow(layers[i], 4);
		I_1 += M_PI * rho * L * pow((0.5*(2*i+1)*L),2) * pow(layers[i],2);
	}
	I_1 += 0.5 * I_3 - m * pow(d, 2);
}

#include <iostream>

Vector GeneralTop::getDDP(Vector P, Vector DP) {
	using namespace constants;

	double cos_theta(cos(P[1]));
	double sin_theta(sin(P[1]));
	
	double d_psi(DP[0]);
	double d_theta(DP[1]);
	double d_phi(DP[2]);

	// Vecteur unitaire dans la direction x vue dans le repère de la toupie
	Vector u(Vector {1.0, 0.0, 0.0});
	// Moment de la force de gravitation par rapport à A
	Vector M_A(m * g * d * sin_theta * u);
	// Matrice d'inertie en A
	Matrix3x3 I_A(getInertiaMatrixA());

	// Vitesse de rotation du repère
	Vector omega_e { d_theta, d_psi * sin_theta, d_psi * cos_theta };
	// Vitesse de rotation de la toupie
	Vector omega(omega_e + Vector{0, 0, d_phi});
	
	// Dérivée d'omega
	// On utilise la simplification dI_A = 0
	Vector d_omega(M_A - (omega_e ^ (I_A * omega)));// - dI_A * omega);
	d_omega = I_A.inv() * d_omega;

	// On calcule les valeurs de DDP
	double d2_theta(d_omega[0]);
	double d2_psi(0);
	double d2_phi(d_omega[2]);
	// Si theta n'est pas nul
	if (!math::isEqual(theta(), 0.0)) {
		d2_psi += (d_omega[1] - d_psi * d_theta * cos_theta) / sin_theta;
		d2_phi += (d_psi * d_theta - d_omega[1] * cos_theta) / sin_theta;
	}
	// Déplacement de la toupie
	double d_x(0);
	double d_y(0);

	// On sauvegarde la valeur de DDP pour pouvoir l'utiliser pour
	// l'affichage sans la recalculer
	DDP_cache = Vector{d2_psi, d2_theta, d2_phi, d_x, d_y};
	return DDP_cache;
}

Vector GeneralTop::getAG() const {
	Vector AG({0, 0, getDistAG()});
	AG = getMatrixToGlobal() * AG;
	return AG;
}

// Methode d'affichage
std::ostream& GeneralTop::print(std::ostream& os) const{
		return os << "Toupie générale" << std::endl
       << "paratmètre : " << getP() << std::endl
       << "dérivée    : " << getDP() << std::endl
       << "masse volumique (kg m-3) : " << getDensity() << std::endl
       << "couches    : " << getLayers() << std::endl
       << "épaisseur des couches    : " << getThickness() << std::endl
       << "masse      : " << getMass() << std::endl;
}
