#include "view_test.h"
#include <iostream>
#include <fstream>


void ViewTest::drawTop(Top const& top){
	Vector a(top.getP());
	const char* add(top.getAddress());
	std::ofstream out(add, std::ios::out|std::ios::app);
	out << top.getTime() << " " << a[0] << " " << a[1] << " " << a[2] << std::endl;
	out.close();

	}









