#pragma once

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "view.h"
#include "top.h"

class ViewOpenGL : public View {
	public:
		virtual void draw(SimpleCone const& top) override;
		void init();
		void setProjection(QMatrix4x4 const& projection) {
			prog_.setUniformValue("projection", projection);
		}
	
	private:
		QOpenGLShaderProgram prog_;
};
