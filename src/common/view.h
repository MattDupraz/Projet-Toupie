#pragma once

class Top;

class View {
	public:
		virtual ~View() {}
		virtual void draw(Top const& top) = 0;
};
