#pragma once

#include "top.h"
#include "system.h"
#include "top_simple_cone.h"
#include "top_gyroscope.h"
#include "top_general.h"
#include "top_chinese.h"

#include <map>
#include <fstream>
#include <memory>

class ViewFile : public View {
public:
	ViewFile();
	~ViewFile() override;

	// Dessine une toupie generique
	void drawTop(Top const& top);

	// Dessine les objets dessinables specifiques
	virtual void draw(SimpleCone const& top) override { drawTop(top); }
	virtual void draw(Gyroscope const& top) override { drawTop(top); }
	virtual void draw(GeneralTop const& top)override { drawTop(top); }
	virtual void draw(ChineseTop const& top) override { drawTop(top); }
	virtual void draw(System const& system) override;
private:
	std::map<unsigned int, std::shared_ptr<std::ofstream>> files;
};
