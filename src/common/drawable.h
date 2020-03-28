#pragma once

#include <memory>
#include <utility>

class View;

class Drawable {
	public:
		Drawable(std::shared_ptr<View> v)
			: view_(std::move(v))
		{}

		virtual ~Drawable() {}

		virtual void draw() const = 0;

	protected:
		std::shared_ptr<View> view_;
};
