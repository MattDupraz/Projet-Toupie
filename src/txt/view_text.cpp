#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::drawTop(Top const& top) {
	if (verbose) {
		std::cout << "\tparamètre: " << top.getP() << std::endl
			<< "\tdérivée : " << top.getDP() << std::endl
			<< "\tEnergie : " << top.getEnergy() << std::endl
			<< "\tProjection L sur a : " 
			<< top.getAngMomentumA()[2] << std::endl
			<< "\tProjection L sur k : " 
			<< (top.getOrientationMatrix() * top.getAngMomentumA())[2]
		  		<< std::endl
			<< "\tProduit mixte : " << top.getProduitMixte() << std::endl;
	} else {
		std::cout << top.getP() << '\t' << top.getDP() << "\t" 
				  << top.getEnergy() << "\t" 
				  << top.getAngMomentumA()[2] << "\t" 
				  << (top.getOrientationMatrix() * top.getAngMomentumA())[2] << "\t"
				  << top.getProduitMixte() << std::endl;
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







