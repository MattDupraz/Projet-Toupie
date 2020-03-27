#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::draw(SimpleCone const& top) {
	std::cout << "Conique simple" << std::endl;
	
	std::cout << "parametre : " << top.getP() << std::endl;
	std::cout << "derivee : " << top.getDP() << std::endl;
  	std::cout << "masse volumique (kg m-3) : " << top.getDensity() << std::endl;
  	std::cout << "hauteur (m) : " << top.getHeight() << std::endl;
  	std::cout << "rayon (m) : " << top.getRadius() << std::endl;
}

void ViewText::print(Top const& top)const {
	std::cout << top.getP() << "   " << top.getDP() << std::endl;
	
	
}







