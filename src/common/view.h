#pragma once

class SimpleCone;

class View {
	public:
		virtual ~View() {}
		virtual void draw(SimpleCone const& top) = 0;
};
