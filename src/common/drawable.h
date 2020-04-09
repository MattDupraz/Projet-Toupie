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

		// Methode pour dessiner un objet dessinable
		// permet le single dispatch
		virtual void draw() const = 0;

	protected:
		// Supprt de dessin utilise
		std::shared_ptr<View> view_;
};
