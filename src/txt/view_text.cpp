#include <iostream>
#include "view_text.h"
#include "top.h"

void ViewText::draw(SimpleCone const& top) {
	std::cout << top.getP()
	  << " " << top.getDP()
  		<< " " << top.getDDP(top.getP(), top.getDP())  << std::endl;
}













