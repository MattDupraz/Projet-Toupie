#include "top_general.h"
#include "math.h"

GeneralTop::GeneralTop(std::shared_ptr<View> v, Vector const& A,
			Vector const& P, Vector const& DP,
			double rho, Vector layers, double thickness)
	:NonRollingTop(std::move(v), A, P, DP), rho(rho), layers(layers), L(thickness)
{
	init_mass();
	init_CM();
	init_I();
}

// Methode d'affichage
std::ostream& GeneralTop::print(std::ostream& os) const{
		return os << "Toupie générales" << std::endl
       << "paratmètre : " << getP() << std::endl
       << "dérivée    : " << getDP() << std::endl
       << "masse volumique (kg m-3) : " << getDensity() << std::endl
       << "layers     : " << getLayers() << std::endl
       << "épaisseur : " << getThickness() << std::endl
       << "masse     : " << getMass() << std::endl;
}

void GeneralTop::init_mass(){
	for (size_t i(0); i < layers.size() ; ++i){
		m+= M_PI*rho*L*layers[i]*layers[i];
	}
}

void GeneralTop::init_CM(){
	double a(0);
	double b(0);
	for (size_t k(0); k < layers.size() ; ++k){
		double r2 = pow(layers[k], 2);
		a += r2;
		b += (2*k+1) * 0.5 * L * r2;	
	}	
	d = b/a;
}		
		
void GeneralTop::init_I(){
	for (size_t i(0); i < layers.size(); ++i){
		I_3 += M_PI * 0.5 * rho * L * pow(layers[i], 4);
		I_1 += M_PI * rho * L * pow((0.5*(2*i+1)*L),2) * pow(layers[i],2);
	}
	I_1 += 0.5 * I_3 - m * pow(d, 2);
}
