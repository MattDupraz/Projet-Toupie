#pragma once

#include "top.h"

class View {
	public:
		virtual ~View() {}
		virtual void draw(Top const& top) = 0;
};
