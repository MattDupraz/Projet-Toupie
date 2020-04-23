#include <iostream>
#include <fstream>

#include "tests.h"
#include "vect.h"
#include "matrix_3x3.h"
#include "view_text.h"
#include "system.h"
#include "integrator.h"
#include <memory>
#include <utility>

using namespace std;

void Tests::testVector() {	
	cout << endl << "-= BEGIN TEST VECTOR =-" << endl << endl;

	Vector v1{1.0, 2.0, 3.0};
	Vector v2{-1.0, -1.5, 2.0};

	cout << "v1 = " << v1 << endl;
	cout << "v2 = " << v2 << endl;

	cout << "v1[2] = " << v1[2] << endl;
	v1[2] = 2.3;
	cout << "v1[2] := 2.3 -> v1 = " << v1 << endl;
	cout << "v1[2] = " << v1[2] << endl;

	cout << "v1 + v2 = " << (v1 + v2) << endl; // addition
	cout << "v2 + v1 = " << (v2 + v1) << endl;

	cout << "v1 ^ v2 = " << (v1 ^ v2) << endl; // produit vectoriel
	cout << "v2 ^ v1 = " << (v2 ^ v1) << endl;

	cout << "v1 * v2 = " << (v1 * v2) << endl; // produit scalaire
	cout << "v2 * v1 = " << (v2 * v1) << endl;

	cout << "3.0 * v1 = " << (3.0 * v1) << endl; // multiplication scalaire
	cout << "v2 * 2.5 = " << (v2 * 2.5) << endl;

	cout << "v1 - v2 = " << (v1 - v2) << endl; // soustraction
	cout << "v2 - v1 = " << (v2 - v1) << endl;

	cout << "v1.norm() = " << v1.norm() << endl; // norme
	cout << "v1.norm2() = " << v1.norm2() << endl; // norme caree
	cout << "v2.norm() = " << v2.norm() << endl;
	cout << "v2.norm2() = " << v2.norm2() << endl;

	cout << "-v1 = " << -v1 << endl; // oppose
	cout << "-v2 = " << -v2 << endl;

	cout << "~v1 = " << ~v1 << endl; // unitaire
	cout << "~v2 = " << ~v2 << endl;

	cout << "v1 == {1.0, 2.0, 2.3} -> " << (v1 == Vector {1.0, 2.0, 2.3}) << endl;
	cout << "v1 != v2 -> " << (v1 != v2) << endl;

	v1 *= -1.7;
	cout << "v1 *= -1.7 -> v1 = " << v1 << endl;

	v1 += v2;
	cout << "v1 += v2 -> v1 = " << v1 << endl;

	v2 -= v1;
	cout << "v2 -= v1 -> v2 = " << v2 << endl;

	cout << endl << "-= END TEST VECTOR =-" << endl << endl;

}

void Tests::testMatrix3x3() {

	cout << endl << "-= BEGIN TEST MATRIX 3X3 =-" << endl << endl;

	Matrix3x3 A;
	cout << "A = " << endl << A;

	A.addLine(1, 0, 3.0);
	cout << "A.addLine(1, 0, 3.0) -> A = " << endl << A;
	A.addLine(2, 1, 2.3);
	cout << "A.addLine(2, 1, 2.3) -> A = " << endl << A;
	A.addLine(0, 2, 1.7);
	cout << "A.addLine(0, 2, 1.7) -> A = " << endl << A;
	A.addLine(2, 1, 1.2);
	cout << "A.addLine(2, 1, 1.2) -> A = " << endl << A;
	A.swapLines(1, 2);
	cout << "A.swapLines(1, 2) -> A = " << endl << A;
	A.multLine(1, 1.3);
	cout << "A.multLine(1, 1.3) -> A = " << endl << A;
	cout << "3.2 * A = " << endl << 3.2 * A;

	Matrix3x3 B({{1, 2, 3}, {2, 1, 3}, {4, 2, 1}});
	cout << "B = " << endl << B;
	cout << "B == Matrix3x3({{1, 2, 3},{2, 1, 3},{4, 2, 1}}) -> " 
		<< (B == Matrix3x3({{1, 2, 3}, {2, 1, 3}, {4, 2, 1}})) << endl;
	cout << "A != B -> " << (A != B) << endl;

	cout << "A * B = " << endl << A * B;
	cout << "B * A = " << endl << B * A;

	cout << "A + B = " << endl << A + B;
	cout << "B + A = " << endl << B + A;

	Vector v{2.3, 1.2, 5.7};
	cout << "v = " << v << endl;
	cout << "A * v = " << A * v << endl;

	cout << "A.inv() -> " << endl << A.inv();

	cout << "A.inv() * A = " << endl << A.inv() * A;
	cout << "A * A.inv() = " << endl << A * A.inv();

	cout << "A.transp() -> " << endl << A.transp();
	cout << "A.det() -> " << A.det() << endl;

	cout << endl << "-= END TEST MATRIX 3X3 =-" << endl << endl;

}

void Tests::testTop(){
	
	cout << "-= BEGIN TEST TOP =-" << endl;
	
	shared_ptr<View> view(new ViewText);
	
	shared_ptr<Integrator> integrator = make_shared<NewmarkIntegrator>();
	// Initialise le systeme
	System system(view, integrator);
	// Ajoute des toupies au systeme
	system.add(make_unique<Gyroscope>(view, 
		Vector {0, 0, 0}, 
		Vector {0, 0.5, 0}, 
		Vector {0, 0, 160},
		1.0, 0.1, 0.2, 1.0));
	system.add(make_unique<SimpleCone>(view,
		Vector {0, 0, 1}, 
		Vector {0,0.5,0}, 
		Vector {0,0,70},
		0.1, 1.5, 0.75));
	
	std::cout << system;
	
	cout << "-= END TEST TOP =-" << endl;
	
	}

void Tests::testIntegration() {

	cout << "-= BEGIN TEST INTEGRATOR =-" << endl;

	size_t nbrepet(1000);
	constexpr double dt(0.01);

	shared_ptr<View> view(new ViewText);

	shared_ptr<Integrator> integrator = make_shared<NewmarkIntegrator>();
	// Initialise le systeme
	System system(view, integrator);
	// Ajoute des toupies au systeme
	system.add(make_unique<Gyroscope>(view, 
		Vector {0, 0, 0}, 
		Vector {0, 0.5, 0}, 
		Vector {0, 0, 160},
		1.0, 0.1, 0.2, 1.0));
	system.add(make_unique<SimpleCone>(view,
		Vector {0, 0, 1}, 
		Vector {0,0.5,0}, 
		Vector {0,0,70},
		0.1, 1.5, 0.75));
		
	string file1("./tests/test_cone_simple.txt");
	string file2("./tests/test_gyroscope.txt");

	cout << "Opening file " << file1 << "..." << endl;
	ofstream out1(file1);
	cout << "- Done!" << endl;

	cout << "Opening file " << file2 << "..." << endl;
	ofstream out2(file2);
	cout << "- Done!" << endl;

	cout << "Running simulation..." << endl;
	for (size_t i(0); i < nbrepet ; ++i){
		system.evolve(dt);

		out1 << system.getElapsedTime() << " " << system.getTop(0).getP() << endl;
		
		out2 << system.getElapsedTime() << " " << system.getTop(1).getP() << endl;
	}
	cout << "- Done!" << endl;

	cout << "Closing file " << file1 << "..." << endl;
	out1.close();
	cout << "Closing file " << file2 << "..." << endl;
	out2.close();
	cout << "- Done!" << endl;
		
	cout << "-= TEST INTEGRATOR =-" << endl;
}
