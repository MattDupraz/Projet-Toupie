#include <iostream>
#include "view_file.h"
#include "top.h"

#include "stdlib.h"
#include <sstream>

ViewFile::ViewFile() {
	system("mkdir -p out");
}

ViewFile::~ViewFile() {
	for (auto& entry : files) {
		entry.second->close();
	}
}

void ViewFile::drawTop(Top const& top) {
	*(files[top.objectID]) << top.getP() << '\t'
		<< top.getDP() << '\t'
		<< top.getEnergy() << '\t'
		<< top.getAngMomentumA()[2] << '\t'
		<< (top.getOrientationMatrix() * top.getAngMomentumA())[2] << '\t'
		<< top.getProduitMixte() << std::endl;
}

void ViewFile::draw(System const& system) {
	for (std::size_t i(0); i < system.size(); ++i) {
		Top const& top = system.getTop(i);
		auto iter = files.find(top.objectID);
		if (iter == files.end()) {
			std::ostringstream filename;
			filename << "out/top" << top.objectID << ".txt";
			files[top.objectID] = std::make_shared<std::ofstream>();
			files[top.objectID]->open(filename.str());
			*(files[top.objectID])
				<< "# paramètre\tdérivée\ténergie\tL_Ak\tL_Aa\tproduit mixte"
				<< std::endl;
		}
		*(files[top.objectID]) << system.getElapsedTime() << '\t';
		system.getTop(i).draw();
	}
}







