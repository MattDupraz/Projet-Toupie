#pragma once

#include "top.h"
#include "system.h"

class ViewText : public View {
public:
	ViewText(bool verbose = false)
		: verbose(verbose)
	{}

	virtual void draw(SimpleCone const& top) override;
	virtual void draw(System const& system) override;

	void setVerbose(bool val) {verbose = val;}
private:
	bool verbose;
};
