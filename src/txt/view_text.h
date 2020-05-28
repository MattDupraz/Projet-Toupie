#pragma once

#include "tops.h"
#include "system.h"

class ViewText : public View {
public:
	ViewText(){}

	// Dessine une toupie generique
	void drawTop(Top const& top);

	// Dessine les objets dessinables specifiques
	virtual void draw(SimpleCone const& top) override { drawTop(top); }
	virtual void draw(Gyroscope const& top) override { drawTop(top); }
	virtual void draw(GeneralTop const& top)override { drawTop(top); }
	virtual void draw(ChineseTop const& top) override { drawTop(top); }
	virtual void draw(System const& system) override;
};
