#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::draw(Top const& top) {
	std::cout << " Position 	  	: " << top.getFD() << std::endl;
	std::cout << " Vitesse		  	: " << top.getDD() << std::endl;
}













