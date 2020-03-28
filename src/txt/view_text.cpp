#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::draw(SimpleCone const& top) {
	if (verbose) {
		std::cout << "\tparamètre: " << top.getP() << std::endl
			<< "\tdérivée : " << top.getDP() << std::endl;
	} else {
		std::cout << top.getP() << '\t' << top.getDP() << std::endl;
	}
}

void ViewText::draw(System const& system) {
	if (verbose) {
		std::cout << "t = " << system.getElapsedTime() << std::endl;
		for (std::size_t i(0); i < system.size(); ++i) {
			std::cout << "toupie #" << i + 1 << ": " << std::endl;
			system.getTop(i).draw();
		}
	}	else {
		for (std::size_t i(0); i < system.size(); ++i) {
			std::cout << i + 1 << '\t' << system.getElapsedTime() << '\t';
			system.getTop(i).draw();	
		}
	}

}







