#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::draw(Top const& top) {
	std::cout << " Position 	  	: " << top.getPos() << std::endl;
	std::cout << " Vitesse		  	: " << top.getVel() << std::endl;
	std::cout << " Angle d'Euler  	: " << top.getAngPos() << std::endl;
	std::cout << " Vitesse d'Euler	: " << top.getAngVel() << std::endl;
}













