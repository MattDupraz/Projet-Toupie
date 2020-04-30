#pragma once

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

template <class T>
class UniformValue {
	public:
		UniformValue();

		T& value() { return val; }
		void setValue(T const& v) {
			val = v;
			update();
		}

		void bind(QOpenGLShaderProgram* prog, const char* name);
		void update();
		void reset();

	protected:
		virtual T defaultValue() = 0;

	private:
		QOpenGLShaderProgram* prog;
		int location;
		T val;
};

class UniformMatrix4x4 : public UniformValue<QMatrix4x4> {
	public:
		UniformMatrix4x4() : UniformValue<QMatrix4x4>() {}
	protected:
		virtual QMatrix4x4 defaultValue() override { return QMatrix4x4(); }
};
