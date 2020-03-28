#pragma once

class SimpleCone;
class System;

class View {
	public:
		virtual ~View() {}
		virtual void draw(SimpleCone const& top) = 0;
		virtual void draw(System const& system) = 0;
};
