#pragma once

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

template <class T>
class UniformValue {
	public:
		UniformValue(T val);

		// Le type de retour est une référence modifiable,
		// ceci nous permet de modifier la valeur à travers ses methodes
		T& value() { return val; }
		// Affecte la valeur (CPU)
		void setValue(T const& v) { val = v; }
		
		// La methode `bind` DOIT être appellée avant que `update` ne soit utilisée
		void bind(QOpenGLShaderProgram* prog, const char* name);
		// Met à jour la valeur uniforme dans le GPU
		void update();
		// Réinitialise la valeur (CPU)
		virtual void reset() = 0;

	protected:
		QOpenGLShaderProgram* prog;
		int location;
		T val;
};

class UniformMatrix4x4 : public UniformValue<QMatrix4x4> {
	public:
		UniformMatrix4x4() : UniformValue<QMatrix4x4>(QMatrix4x4()) {}
		virtual void reset() override { val.setToIdentity(); }
}; 
