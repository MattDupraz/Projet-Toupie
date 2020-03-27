#pragma once

#include "top.h"
#include "integrator.h"
#include <vector>
#include <iostream>


class System : public Drawable{
	public :
		

		void draw(){
			for (std::size_t i(0); i<list_top.size(); ++i){
				std::cout << "==== Toupie " << i+1 << " :" << std::endl;
				(*list_top[i]).draw();	
			}	
		}

		void evolve(double dt){
			for (auto& ptr : list_top){
				(*integ).evolve((*ptr), dt);
				(*ptr).print();
			}
			std::cout << std::endl;
		}

		void add(Top* t){
			list_top.push_back(t);
		}

		void printSystem(){
			for (auto& ptr : list_top){
				this->draw();
			}
		}

		System(View* v,Top* t, Integrator* i)
		:Drawable(v),integ(i)
		{	
		list_top.push_back(t);
		}
		
		~System(){
		for (auto& ptr : list_top){
			ptr = nullptr; 		
			}
		}
	private :
		std::vector<Top*> list_top;

		Integrator* integ;


};
