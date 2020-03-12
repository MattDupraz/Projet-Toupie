#include <QApplication>
#include "gl_widget.h"

int main(int argc, char* argv[]) {
	// Cree une instance de QApplication - la fenetre
	QApplication a(argc, argv);
	// Ajoute le GLWidget qu'on a cree a l'affichage de la fenetre
	GLWidget w;
	w.show();
	// Met en route le programme - voir gl_widget.cpp
	return a.exec();
}
