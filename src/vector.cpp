#include <iostream>
#include <cmath>
#include <vector>
#include <stdarg.h>
using namespace std;


class Vecteur{
	public : 
		// Constructeur
		Vecteur(double c1=0.0,...)
		:len_(1)
		{coord_.push_back(c1);}
		
		Vecteur(vector<double> v,size_t t)
		:coord_(v),len_(t)
		{}
		
		// Méthodes
	
		void print()const;
		
		void augment(double num);
		
		void set_coord(size_t ind, double num);
		
		bool is_equal(Vecteur const&)const;
		
		Vecteur negative()const;
		
		double prod_scal(Vecteur const& v)const;
		
		Vecteur mult(double scal)const;
		
		double norme()const;
		
		double norme2()const;
		
		Vecteur unit()const;
		
		size_t len()const{
			return len_;
			}
		
		double coord(size_t i){
			return coord_[i];
			}
		
	private : 
	
		vector<double> coord_;
		
		size_t len_;
			
	
	};
	
	
//###########################################################	
//################ Definition des operateurs ################
//###########################################################	

	
// définition d'un operateur qui teste l'egalite
// entre 2 vecteur

bool operator==(Vecteur const& v1, Vecteur const& v2){
	return v1.is_equal(v2);
	}

// Methode qui teste l'égalité entre 2 vecteurs

bool Vecteur::is_equal(Vecteur const& v)const{
	bool rep(true);
	if (len_!=v.len_){
		rep=false;
		}
	else{
		for (size_t i(0);i<v.len_;++i){
			if (not(abs(v.coord_[i]-coord_[i])<1e-10)){
				rep=false;
				}
			}
		}
	return rep;
	}
	

	
// definition de l'operateur produit scalaire

double operator*(Vecteur const& v1, Vecteur const& v2){
	return v1.prod_scal(v2);
	}
	
// definition de la methode produit scalaire

double Vecteur::prod_scal(Vecteur const& v)const{
	double res(0);
	
	for (size_t i(0);i<min(len_,v.len_);++i){
		res+=coord_[i]*v.coord_[i];
		}
	return res;
	}	

// definition de l'operateur multiplication par un scalaire

Vecteur operator*(Vecteur const& v, double const& scal){
	return v.mult(scal);
	}
	
Vecteur operator*(double const& scal, Vecteur const& v){
	return v.mult(scal);
	}
	

Vecteur Vecteur::mult(double scal)const{
	Vecteur v;
	v.coord_=coord_;
	v.len_=len_;
	for (size_t i(0);i<v.len_;++i){
		v.coord_[i]=scal*coord_[i];
		}
	return v;
	}
	
	
// Definition de l'addition
Vecteur operator+(Vecteur& w, Vecteur& v){
	Vecteur u(v);	
	u.set_coord(0,w.coord(0)+v.coord(0));	
	for (size_t i(1); i < min(v.len(), w.len());i++){
		u.set_coord(i,w.coord(i)+v.coord(i));
		}
	return u;
	}

// Operateur produit vectoriel

Vecteur operator^(Vecteur& w, Vecteur& v){
	Vecteur u(w);
	u.set_coord(0, w.coord(1)*v.coord(2) - w.coord(2)*v.coord(1));
	u.set_coord(1, w.coord(2)*v.coord(0) - w.coord(0)*v.coord(2));
	u.set_coord(2, w.coord(0)*v.coord(1) - w.coord(1)*v.coord(0));
	return u;
	}


// Operateur soustraction
Vecteur operator-(Vecteur& w, Vecteur& v){
	Vecteur u(v);	
	u.set_coord(0,w.coord(0)-v.coord(0));	
	for (size_t i(1); i < min(v.len(), w.len());i++){
		u.set_coord(i,w.coord(i)-v.coord(i));
		}
	return u;
	}


//###########################################################	
//################ Definition des methodes ##################
//###########################################################



// Fonction qui ajoute une coordonnee au vecteur

void Vecteur::augment(double num){
	coord_.push_back(num);
	len_+=1;
	}

// Fonction afficher le vecteur

void Vecteur::print() const{
	for (auto& co : coord_){
		cout << co << "  ";
		}
	cout << endl;
	}

//Fonction qui modifie une composante du vecteur

void Vecteur::set_coord(size_t ind, double num){
	coord_[ind]=num;
	}

Vecteur Vecteur::negative()const{
	Vecteur v;
	v.set_coord(0,-coord_[0]);
	for (size_t i(1); i<len_; ++i){
		v.augment(-coord_[i]);
		}
	return v;
	}

double Vecteur::norme()const{
	double res(0);
	for (auto n : coord_){
		res += n*n;
		}
	return sqrt(res);
	}
		
double Vecteur::norme2()const{
	double res(0);
	for (auto n : coord_){
		res += n*n;
		}
	return res;
	
	}


Vecteur Vecteur::unit()const{
	double res(0);
	for (auto n : coord_){
		res += n*n;
		}
	Vecteur vect(coord_,len_);
	return (1/sqrt(res))*vect;
	}


int main(){
	Vecteur v1(1);
	Vecteur v2(2);
	
	v1.augment(1);
	v2.augment(1);
	
	v1.augment(0);
	v2.augment(0);
	
	v1.print();
	v2.print();

	Vecteur v3(v1^v2);
	v3.print();
	v2.unit().print();
	return 0;
	}
