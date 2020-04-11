#pragma once

#include <iostream>
#include <fstream>
#include "top.h"
#include "system.h"


class ViewTest : public View {
public:
	ViewTest(){}

	~ViewTest(){}
	// Dessine une toupie generique
	void drawTop(Top const& top);

	// Dessine les objets dessinables specifiques
	virtual void draw(SimpleCone const& top) override { drawTop(top);}
	virtual void draw(Gyroscope const& top) override { drawTop(top); }
	virtual void draw(System const& system) override{
		for(std::size_t i(0); i < system.size(); ++i){
			system.getTop(i).draw();
		}

	}

};
