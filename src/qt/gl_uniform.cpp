#include "gl_uniform.h"
#include "assert.h"
	
template <class T>
UniformValue<T>::UniformValue()
	: prog(nullptr), location(-1) {}

template <class T>
void UniformValue<T>::bind(QOpenGLShaderProgram* sp, const char* name) {
	assert(sp != nullptr);
	prog = sp;
	location = prog->uniformLocation(name);
	reset();
}

template <class T>
void UniformValue<T>::update() {
	assert(prog != nullptr);
	assert(location != -1);

	prog->setUniformValue(location, val);
}

template <class T>
void UniformValue<T>::reset() {
	val = defaultValue();
	update();
}

template class UniformValue<QMatrix4x4>;
