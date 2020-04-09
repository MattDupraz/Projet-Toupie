#pragma once

#include "top.h"
#include "system.h"

class ViewText : public View {
public:
	ViewText(bool verbose = false)
		: verbose(verbose)
	{}

	// Dessine une toupie generique
	void drawTop(Top const& top);

	// Dessine les objets dessinables specifiques
	virtual void draw(SimpleCone const& top) override { drawTop(top); }
	virtual void draw(Gyroscope const& top) override { drawTop(top); }
	virtual void draw(System const& system) override;

	// Change l'option `verbose`
	void setVerbose(bool val) {verbose = val;}
private:
	// verbose = true affiche les donnees d'une maniere lisible pour l'utilisateur
	// verbose = false affiche les donnees d'une maniere adaptee pour gnuplot
	bool verbose;
};
