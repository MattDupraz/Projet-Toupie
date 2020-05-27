#include "tests.h"

int main() {
	// Changer selon les besoins
	const bool TEST_VECTOR = true;
	const bool TEST_MATRIX = true;
	const bool TEST_INTEGRATOR = true;
	const bool TEST_TOP = true;

	// On effectue les tests
	if (TEST_VECTOR)
		tests::testVector();
	if (TEST_MATRIX)
		tests::testMatrix3x3();
	if (TEST_TOP)
		tests::testTop();
	if (TEST_INTEGRATOR)
		tests::testIntegration();
	
		
}
