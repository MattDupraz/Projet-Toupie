#include <iostream>
#include "view_file.h"
#include "top.h"

#include "stdlib.h"
#include <sstream>

ViewFile::ViewFile() {
	// On essaie de créer le répertoire `out`
	// rmq: marche seulement sous Linux!
	std::cout << "Création du répertoire out/..." << std::endl;
	system("mkdir -p out");
}

ViewFile::~ViewFile() {
	// On ferme tous les streams ouvert
	std::cout << "Fermeture des fichiers..." << std::endl;
	for (auto& entry : files) {
		entry.second->close();
	}
}

void ViewFile::drawTop(Top const& top) {
	// A ce point le stream existe forcément
	*(files[top.objectID]) << top.getP() << '\t'
		<< top.getDP() << '\t'
		<< top.getEnergy() << '\t'
		<< top.getAngMomentumA()[2] << '\t'
		<< (top.getMatrixToGlobal() * top.getAngMomentumA())[2] << '\t'
		<< top.getMixedProduct() << std::endl;
}

void ViewFile::draw(System const& system) {
	for (std::size_t i(0); i < system.size(); ++i) {
		Top const& top = system.getTop(i);
		auto iter = files.find(top.objectID);
		// Si iter == files.end(), alors le dictionnaire ne contient pas
		// le ofstream pour cette toupie
		if (iter == files.end()) {
			// On ouvre le ofstream
			std::ostringstream filename;
			// Nom du fichier utilise l'ID comme identifiant
			filename << "out/top" << top.objectID << ".txt";
			// Le stream est fermé quand la vue est détruite
			std::shared_ptr<std::ofstream> strm = std::make_shared<std::ofstream>();

			std::cout << "Ouverture du fichier " << filename.str() << "..." << std::endl;
			strm->open(filename.str());

			// Légende au début du fichier
			*strm << "# paramètre\tdérivée\ténergie\tL_Ak\tL_Aa\tproduit mixte"
				<< std::endl;

			files[top.objectID] = strm;
		}
		*(files[top.objectID]) << system.getElapsedTime() << '\t';
		system.getTop(i).draw();
	}
}







