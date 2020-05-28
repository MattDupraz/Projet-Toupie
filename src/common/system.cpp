#include "system.h"

// Evolue le systeme en fonction du pas de temps dt
void System::evolve(double dt){
	t += dt;
	for (std::unique_ptr<Top>& top : tops){
		integrator->evolve(*top, dt);
	}
}

// Affiche les details du systeme dans ostream
std::ostream &operator<<(std::ostream& os, System const& system) {
	os << "Le système est constitué de " << system.size()
		<< " toupies:\n" << std::endl;
	for (std::size_t i(0); i < system.size(); ++i) {
		os << "==== Toupie #" << i + 1 << std::endl;
		os << system.getTop(i);
		os << std::endl;
	}
	return os;
}












