#include <iostream>
#include <memory>
#include <stdlib.h>

//#include "top.h"

using namespace std;
/*
unique_ptr<SimpleCone> parseSimpleCone(char** argv) {
	return nullptr;
}

unique_ptr<Gyroscope> parseGyroscope() {
	return nullptr;
}*/

void usage() {
	cout << "Usage: app [arguments] [tops]\n\n"
		  << "Arguments:\n"
		  << '\t' << "-g or --gui" << '\t' << "Graphical real-time simulation\n"
		  << '\t' << "-v or --verbose" << '\t' << "Verbose mode\n"
		  << '\t' << "-t or --test" << '\t' << "Run tests (only)\n"
		  << '\t' << "-h or --help" << '\t' << "Display this help message\n"
		  << '\t' << "-s or --steps <num>" << '\t' << "Simulate <num> steps\n"
		  << '\t' << "--dt <ms>" << '\t' << "Set time step (in milliseconds)\n"
		  << '\t' << "-i or --integrator <EulerCromer|Newmark|RungeKutta>" << '\t' << "Use the chosen integrator (default = RungeKutta)"
		  << '\n'
		  << "Tops:\n"
		  << '\t' << "SimpleCone <x> <y> <z> <psi> <theta> <phi> <d_psi> <d_theta> <d_phi> <rho> <L> <R>\n"
		  << '\t' << "Gyroscope <x> <y> <z> <psi> <theta> <phi> <d_psi> <d_theta> <d_phi> <d> <rho> <L> <R>"
		 << endl; 
}

int main(int argc, char** argv) {
	usage();
}
