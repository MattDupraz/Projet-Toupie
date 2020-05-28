#ifdef VER_GRAPHIC
	#include <QApplication>
	#include "gl_widget.h"
	#include "view_opengl.h"
#endif

#ifdef VER_TEXT
	#include "view_text.h"
	#include "view_file.h" 
#endif

#include "system.h"
#include "integrators.h"
#include "tops.h"
#include "vect.h"
#include "math.h"

#include <memory>
#include <utility>
#include <iostream>

using namespace std;

// Paramètres numériques:

// pas de temps
const double DT = 10;
// nombre d'itérations (pour la version texte)
const int N_ITERATIONS = 2000;

// Modifier ici pour choisir l'intégrateur
// Intégrateurs disponibles:
//   - EulerCromerIntegrator
//   - RungeKuttaIntegrator
//   - NewmarkIntegrator
// (ils sont définis dans le répertoire `src/common`)
shared_ptr<Integrator> get_integrator() {
	// Définit l'intégrateur utilisé
	return make_shared<RungeKuttaIntegrator>();
}

// Configurer ici les toupies utilisées
// Toupies disponibles:
//   - SimpleCone
//   - Gyroscope
//   - ChineseTop
//   - GeneralTop
// (elles sont définies dans le répertoire `src/common`,
//  voir les headers pour plus de détails sur leur initialisation)
void add_tops(System& system, shared_ptr<View> view) {
	// Pour ajouteur une toupie:

	// system.add(make_unique<T>(view, ...))

	// où T est le type de la toupie,
	// et les arguments ... sont à compléter selon
	// le constructeur spécifique de la toupie

	// Gyroscope simple
	system.add(make_unique<Gyroscope>(view,
		Vector {-1, -2, 0},
		Vector {0, 0.5, 0},
		Vector {0, 0, 5},
		1.0, 0.1, 0.2, 1.0));

	// Définition de la toupie générale
	// Nombre de couches, plus de couches = plus de précision
	int n_layers = 100;
	Vector layers;
	for (int i(0); i < n_layers; ++i) {
		// valeur interpolée linéairement entre 0 et 1
		double x((double(i) + 0.5) / double(n_layers));
		// fonction de x, la toupie serait un solide de révolution
		// par rapport à cette fonction
		double y(0.75 * abs(sin(M_PI*pow(x, 2.0))));
		layers.augment(y);
	}
	system.add(make_unique<GeneralTop>(view,
		// psi, theta, phi, #, # 
		Vector {0, 0.5, 0, 0, 0},
		// d_psi, d_theta, d_phi, x, y
		Vector {0, 0, 170, -3, 2},
		// rho, layers, thickness
		0.1, layers, 1.5 / double(n_layers)));

	// Cone simple
	system.add(make_unique<SimpleCone>(view,
		// x, y, z
		Vector {2, 1, 0},
		// psi, theta, phi
		Vector {0,0.5,0},
		// d_psi, d_tehta, d_phi
		Vector {0,0,170},
		// rho, hauteur, rayon
		0.1, 1.5, 0.75));

	// Toupie chinoise
	system.add(make_unique<ChineseTop>(view,
		// psi, theta, phi, #, #
		Vector {0,0.5,0, 0, 0},
		// d_psi, d_theta, d_phi, x, y
		Vector {0,0,15, 0, 0},
		// rho, rayon, hauteur tronquée
		0.1, 0.75, 0.6));
}

// Point d'entré du programme
int main(int argc, char* argv[]) {
#ifdef VER_GRAPHIC
	// Initialise le support de dessin
	shared_ptr<ViewOpenGL> view = make_shared<ViewOpenGL>();
#endif
#ifdef VER_TEXT
	shared_ptr<View> view = make_shared<ViewFile>();
#endif
	// Initialise l'integrateur choisi
	shared_ptr<Integrator> integrator = get_integrator();
	// Initialise le systeme
	unique_ptr<System> system = make_unique<System>(view, integrator);
	
	add_tops(*system, view);

	// Affiche les conditions initialles du systeme
	cout << *system;
	
#ifdef VER_GRAPHIC
	// Initialise l'application Qt
	QApplication a(argc, argv);

	GLWidget w(move(system), view, DT);
	// Affiche la fenetre
	w.show();
	// Enclenche la boucle principale du programme
	return a.exec();
#endif
#ifdef VER_TEXT
	cout << "Le système évolue et se dessine à chaque pas (dt = " << DT << "ms): "
			<< endl;
	
	// Evolue le systeme nIterations fois
	for (int i(0); i < N_ITERATIONS; ++i) {
		system->evolve(DT / 1000.0);
		system->draw();
	}
	
	return 0;
#endif
}
