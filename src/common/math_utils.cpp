#include "math.h" // C++ library
#include "math_utils.h"

bool isEqual(double a, double b) {
	return abs(a - b) < D_PREC;
}

double toRadians(double a) {
	return (a / 360.0) * (2 * M_PI);
}

double toDegrees(double a) {
	return (a / (2 * M_PI)) * 360.0;
}

