#include "math.h"
#include "top.h"
#include "constants.h"

// Constructeur d'un cone simple
SimpleCone::SimpleCone(std::shared_ptr<View> v, Vector const& A,
		Vector const& P, Vector const& DP,
		double rho, double L, double R)
	: NonRollingTop(std::move(v), A, P, DP), rho(rho), L(L), R(R)
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
		double d, double rho, double L, double R)
	: NonRollingTop(std::move(v), A, P, DP), rho(rho), L(L), R(R)
{
	this->d = d; // distance du CM du point de contact
	m = M_PI * pow(R, 2) * L * rho; // masse
	I_A1 = 0.25 * m * pow(R, 2); // axe horizontal
	I_A1 += m * pow(d, 2); // loi du transfert
	I_A3 =  0.5 * m * pow(R, 2); // axe vertical
}

// Constructeure de la toupie chinoise
ChineseTop::ChineseTop(std::shared_ptr<View> v,
		Vector const& P,  Vector const& DP,
		double rho, double R, double h)
	: Top(std::move(v), P, DP), h(h), R(R), rho(rho)
{
	m = M_PI * rho * (4.0/3.0 * pow(R, 3) - pow(h, 2)*(R - 1.0/3.0 * h));
	alpha = (3.0 * pow(h, 2)) / (4 * R * (R + h));
	I_3 = M_PI/30.0 * rho * pow(2.0 * R - h, 3)
		* (2 * pow(R, 2) + 3 * h * R + 3 * pow(h, 2));
	double Z2 = M_PI / 15.0 * rho * pow(2*R - h, 2)
		* (pow(R, 3) + h * pow(R, 2) - 3 * pow(h, 2) * R + 3 * pow(h, 3));
	I_1 = 0.5 * I_3 + Z2 - m * pow(R * alpha, 2);
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

// Methode d'affichage du gyroscope
std::ostream& ChineseTop::print(std::ostream& os) const {
	return os << "Toupie Chinoise" << std::endl
		<< "paramètre : " << getP() << std::endl
		<< "dérivée   : " << getDP() << std::endl
		<< "masse volumique (kg m-3) : " << getDensity() << std::endl
		<< "masse  (kg) : " << getMass() << std::endl
		<< "rayon   (m) : " << getRadius() << std::endl
		<< "hauteur tronquée (m) : " << getTruncatedHeight() << std::endl;
}

// Methode d'affichage
std::ostream& ToupiesGen::print(std::ostream& os) const{
		return os << "Toupie générales" << std::endl
       << "paratmètre : " << getP() << std::endl
       << "dérivée    : " << getDP() << std::endl
       << "masse volumique (kg m-3) : " << getDensity() << std::endl
       << "layers     : " << getlayers() << std::endl
       << "épaisseur : " << getThick() << std::endl;
}

// Operateur d'affichage de la toupie
std::ostream &operator<<(std::ostream& os, Top const& a) {
	return a.print(os);

}

Matrix3x3 Top::getI() const {
	return Matrix3x3({
		{getI_1(),0,0},
		{0,getI_1(),0},
		{0,0,getI_3()}
	});
}
Matrix3x3 Top::getRgToRo() const {
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

double NonRollingTop::getEnergy()const{
	using namespace constants;
	Vector acc{0,0,g};
	
	Matrix3x3 I_A(getI()); // Matrice d'inertie
	Matrix3x3 S(getRgToRo()); // Passage de base
	
	//On doit trouver le vecteur OG = OA + AG mais AG n'est pas connu dans
	//le repere Ro donc il faut utiliser la matrice S (matrice de passage)
	Vector AGg {0,0,d};
	Vector AGo(S*AGg);
	Vector OGo(A+AGo);
	
	double Ec = 0.5*(getDP()*(I_A*getDP()));
	double Eg = -m*(acc*OGo);
	
	return Ec+Eg;
}

double ChineseTop::getEnergy()const{
	using namespace constants;
	Vector acc{0,0,g};
	
	Matrix3x3 I_A(getI()); // Matrice d'inertie
	Matrix3x3 S(getRgToRo()); // Passage de base
	
	//On doit trouver le vecteur OG = OA + AG mais AG n'est pas connu dans
	//le repere Ro donc il faut utiliser la matrice S (matrice de passage)
	Vector AGg({0,0,y()});
	Vector AGo(S*AGg);
	Vector OA({x(),0,z()});
	Vector OGo(OA+AGo);
	
	Vector omega{psi(),theta(),phi()};
	double Ec(omega*(I_A*omega));
	Vector v{d_x(), d_z()};
	Ec += v.norm();
	Ec *= 0.5;
	double Eg = -m*(acc*OGo);
	
	
	return Ec;
}

double NonRollingTop::getL_Ak()const{	
	Matrix3x3 I_A(getI()); // Matrice d'inertie
	Matrix3x3 S(getRgToRo()); // Passage de base
	
	Vector L_A(S*getDP());
	L_A = S*L_A;
	return Vector {0,0,1}*L_A;
}



// Equation du mouvement d'une toupie sans roulement
// c.f. complement mathematique page 12 eq. 13-15
Vector NonRollingTop::getDDP(Vector P, Vector DP) {
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

double ChineseTop::getL_Ak()const{
	double Psi(psi());
	double Theta(theta());
	
	Matrix3x3 I(getI()); // Matrice d'inertie
	Matrix3x3 S(getRgToRo()); // Passage de base
	
	Vector L_A(S*(Vector {psi(),theta(),phi()}));
	L_A = S*L_A;
	return Vector {0,0,1} * L_A;
}

// Equation du mouvement d'une toupie chinoise
// c.f. complement mathematique page 20
Vector ChineseTop::getDDP(Vector P, Vector DP) {
	double cos_theta(cos(P[1]));
	double sin_theta(sin(P[1]));

	double d_psi(DP[0]);
	double d_theta(DP[1]);
	double d_phi(DP[2]);

	// Auxilliary variables
	double mR2 = m * pow(R, 2);

	double f_1(d_phi + d_psi * cos_theta);
	double f_3(I_1 * I_3);
	f_3 += mR2 * pow(sin_theta, 2) * I_1;
	f_3 += mR2 * pow(alpha - cos_theta, 2) * I_3;
	double f_2(d_theta / sin_theta * f_1);
	f_2 *= (I_3 * (I_3 + mR2 * (1.0 - alpha * cos_theta))) / f_3;
	f_2 -= 2 * d_psi * d_theta * (cos_theta / sin_theta);

	double a_1(-mR2 * (alpha - cos_theta) * (1 - alpha * cos_theta));
	a_1 += I_1 * cos_theta;
	a_1 *= pow(d_psi, 2);
	double a_2(mR2 * (alpha * cos_theta - 1) - I_3);
	a_2 *= f_1 * d_psi;
	a_2 -= mR2 * pow(d_theta, 2) * alpha + m * R * alpha * constants::g;
	double a_3(I_1 + mR2 * pow(alpha - cos_theta, 2) + pow(sin_theta, 2));

	double d2_theta(sin_theta * (a_1 + a_2) / a_3);

	double d2_psi(f_2);

	double d2_phi(mR2 * (I_3 * (alpha - cos_theta) + I_1 * cos_theta) / f_3);
	d2_phi *= -f_1 * d_theta * sin_theta;
	d2_phi += d_psi * d_theta * sin_theta - cos_theta * f_2;

	double cos_psi(cos(P[0]));
	double sin_psi(sin(P[0]));

	double d_x(R*(d_theta * sin_psi - d_phi * cos_psi * sin_theta));
	double d_z(-R*(d_theta * cos_psi + d_phi * sin_psi * sin_theta));

	DDP_cache = Vector{d2_psi, d2_theta, d2_phi, d_x, d_z};
	return DDP_cache;
}
//================== Méthodes des toupies générales ==================//

ToupiesGen::ToupiesGen(std::shared_ptr<View> v, Vector const& A,
			Vector const& P, Vector const& DP,
			double rho, std::vector<double> layers, double thickness)
	:NonRollingTop(std::move(v), A, P, DP), rho(rho), layers(layers), L(thickness)
{
	init_mass();
	init_CM();
	init_I_A();
}

void ToupiesGen::init_mass(){
	for (size_t i(0); i < layers.size() ; ++i){
		m+= M_PI*rho*L*layers[i]*layers[i];
	}
}

void ToupiesGen::init_CM(){
	double a(0);
	double b(0);
	for (size_t k(0); k < layers.size() ; ++k){
		double r2 = pow(layers[k], 2);
		a += r2;
		b += (2*k+1) * 0.5 * L * r2;	
	}
	
	d = b/a;
}		
		
void ToupiesGen::init_I_A(){
	for (size_t i(0); i < layers.size(); ++i){
		I_A3 += M_PI * 0.5 * rho * L * pow(layers[i], 4);
		I_A1 += M_PI * rho * L * pow((0.5*(2*i+1)*L),2) * pow(layers[i],2);
	}
	I_A1 += 0.5 * I_A3 - m * pow(d, 2);
}
		
		
