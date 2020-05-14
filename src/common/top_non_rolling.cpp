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
