#include "tests.h"
#include "view_test.h"
#include "system.h"
#include "top.h"
#include "integrator.h"

#include <iostream>
#include <memory>
#include <utility>
using namespace std;

int main() {

	const bool TEST_VECTOR = true;
	const bool TEST_MATRIX = true;
	const bool TEST_INTEGRATOR = true;

	Tests tests;
	if (TEST_VECTOR)
		tests.testVector();
	if (TEST_MATRIX)
		tests.testMatrix3x3();
	if (TEST_INTEGRATOR){              // On teste les différents intégrateurs
		tests.testIntegration();
		}
}
