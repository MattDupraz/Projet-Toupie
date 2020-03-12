#include <iostream>

#include "tests.h"
#include "vect.h"
#include "matrix_3x3.h"
#include "top.h"

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

}

void Tests::testTop() {

}
