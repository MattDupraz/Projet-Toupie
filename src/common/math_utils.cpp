#include <cmath>
#include "math_utils.h"

bool isEqual(double a, double b) {
	return std::abs(a - b) < D_PREC;
}
