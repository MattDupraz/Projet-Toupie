#include "math.h" // C++ library
#include "math_utils.h"

// Compare l'egalite de deux doubles a D_PREC pres
bool isEqual(double a, double b) {
	return abs(a - b) < D_PREC;
}

// Converti des degres en radians
double toRadians(double a) {
	return (a / 360.0) * (2 * M_PI);
}

// Converti des radians en degres
double toDegrees(double a) {
	return (a / (2 * M_PI)) * 360.0;
}

