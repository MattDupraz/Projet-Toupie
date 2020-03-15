#include <iostream>
#include "vect.h"
using namespace std;



class Integrator{
	protected :
	double dt;
	public :
	Integrator(double num)
	:dt(num){}
	
};

class Newmark : public Integrator{
	public :
	void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc);
	
	Newmark(double num, double epsilon=1e-10)
	:Integrator(num){}
	
	void setPrecision(double t){epsilon = t;}
	double getPrecsion(){return epsilon;}
	
	private : 
	double epsilon;
};


void Newmark::integ(Vector& pos, 
					Vector& vel, 
					Vector& acc){
	
	Vector p(pos);
	Vector v(vel);
	Vector a(acc);
	
	
}



class EulerCromerIntegrator : public Integrator{
	public : 
	void integ(Vector& pos, 
			   Vector& vel, 
			   Vector& acc);
	
	EulerCromerIntegrator(double num)
	:Integrator(num){}
};

void EulerCromerIntegrator::integ(Vector& pos, 
								  Vector& vel, 
								  Vector& acc){
	vel =vel+ dt*acc;
	pos =pos+ dt*vel;
	}


int main(){
	Vector pos({0,1,0});
	Vector vel({1,2,0});
	Vector acc({0,0,9.81});
	
	EulerCromerIntegrator  inte(0.002);
	
	
	cout << endl << "===============" << endl;
	cout << " Position     : " << pos << endl;
	cout << " Vitesse      : " << vel << endl;
	cout << " Acceleration : " << acc << endl;
			
	for (size_t i(0); i < 100 ; ++i){
		inte.integ(pos, vel, acc);
		cout << endl << "===============" << endl;
		cout << " Position     : " << pos << endl;
		cout << " Vitesse      : " << vel << endl;
		cout << " Acceleration : " << acc << endl;
	
	
	}






	return 0;
}
