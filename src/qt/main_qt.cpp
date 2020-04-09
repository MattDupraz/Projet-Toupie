#include <QApplication>

#include "gl_widget.h"
#include "system.h"
#include "view_opengl.h"
#include "vect.h"

#include <memory>
#include <utility>

int main(int argc, char* argv[]) {
	std::shared_ptr<ViewOpenGL> view = std::make_shared<ViewOpenGL>();
	std::shared_ptr<Integrator> integrator = std::make_shared<RungeKuttaIntegrator>();

	std::unique_ptr<System> system = std::make_unique<System>(view, integrator);
	system->add(std::make_unique<Gyroscope>(view,
		Vector {-1, 0, -2},
		Vector {0, 0.5, 0},
		Vector {0, 0, 160},
		1.0, 0.1, 0.2, 1.0));
	system->add(std::make_unique<SimpleCone>(view,
		Vector {2, 0, 1},
		Vector {0,0.5,0},
		Vector {0,0,170},
		0.1, 1.5, 0.75));


	QApplication a(argc, argv);
	GLWidget w(std::move(system), view, 20);
	w.show();
	return a.exec();
}
