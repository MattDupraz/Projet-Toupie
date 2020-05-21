#include "gl_uniform.h"
#include "assert.h"
	
template <class T>
UniformValue<T>::UniformValue(T val)
	: prog(nullptr), location(-1), val(val) {}

template <class T>
void UniformValue<T>::bind(QOpenGLShaderProgram* sp, const char* name) {
	assert(sp != nullptr);
	prog = sp;
	location = prog->uniformLocation(name);
	// Si location == -1, la variable n'est pas définie
	assert(location != -1);
	update();
}

template <class T>
void UniformValue<T>::bind(QOpenGLShaderProgram* sp, const char* name,
		T const& val) {
	this->val = val;
	bind(sp, name);
}

template <class T>
void UniformValue<T>::update() {
	// Termine le programme si bind n'a pas été appelé avant d'utiliser update()
	assert(prog != nullptr);
	prog->setUniformValue(location, val);
}

template class UniformValue<QMatrix4x4>;
template class UniformValue<QVector3D>;
template class UniformValue<float>;
