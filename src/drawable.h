#pragma once

class Drawable {
	public:
		Drawable(View v)
			: view_(v)
		{}

		virtual ~Drawable {}

		virtual void draw() = 0;

	protected:
		View* view_;
};
