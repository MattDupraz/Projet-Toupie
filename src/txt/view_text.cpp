#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::drawTop(Top const& top) {
	std::cout << "\tparamètre: " << top.getP() << std::endl
		<< "\tdérivée : " << top.getDP() << std::endl
		<< "\tEnergie : " << top.getEnergy() << std::endl
		<< "\tProjection L sur a : " 
		<< top.getAngMomentumA()[2] << std::endl
		<< "\tProjection L sur k : " 
		<< (top.getOrientationMatrix() * top.getAngMomentumA())[2]
			<< std::endl
		<< "\tProduit mixte : " << top.getProduitMixte() << std::endl;
}

void ViewText::draw(System const& system) {
	std::cout << "t = " << system.getElapsedTime() << std::endl;
	for (std::size_t i(0); i < system.size(); ++i) {
		std::cout << "toupie #" << i + 1 << ": " << std::endl;
		system.getTop(i).draw();
	}
}







