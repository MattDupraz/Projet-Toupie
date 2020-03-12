#include "tests.h"

int main() {

	const bool TEST_VECTOR = true;
	const bool TEST_MATRIX = true;
	const bool TEST_TOP = true;

	Tests tests;
	if (TEST_VECTOR)
		tests.testVector();
	if (TEST_MATRIX)
		tests.testMatrix3x3();
	if (TEST_TOP)
		tests.testTop();
}
