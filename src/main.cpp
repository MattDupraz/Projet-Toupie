#include <QApplication>
#include "gl_widget.h"

//IMPORTS POUR TESTS
#include "vect.h"
#include <iostream>

int main(int argc, char* argv[]) {

	//TESTS DE LA CLASS VECTOR

	Vector v1{1.0, 2.0, 3.0};
	Vector v2{-1.0, -1.5, 2.0};
	std::cout << (v1 + v2) << std::endl; // addition
	std::cout << (v1 ^ v2) << std::endl; // produit vectoriel
	std::cout << (v1 * v2) << std::endl; // produit scalaire
	std::cout << (3.0 * v1) << std::endl; // multiplication scalaire
	std::cout << (v1 - v2) << std::endl; // soustraction
	std::cout << v1.norm() << " " << v1.norm2() << std::endl;
	std::cout << v2.norm() << " " << v2.norm2() << std::endl;
	std::cout << (-v1) << std::endl;
	std::cout << (~v1) << std::endl;

	// FIN DE TESTS

	// Cree une instance de QApplication - la fenetre
	QApplication a(argc, argv);
	// Ajoute le GLWidget qu'on a cree a l'affichage de la fenetre
	GLWidget w;
	w.show();
	// Met en route le programme - voir gl_widget.cpp
	return a.exec();
}
