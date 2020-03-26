#pragma once

#include "top.h"
#include <vector>


class System : public Drawable{
	public :
		System(top const& t)
		{
		top* ptr(nullptr);
		ptr(new top(t));		
		list_top.push_back(ptr);}

		~System()
		{for (auto& ptr : list_top){
			delete ptr;
		}
		}

		System(System const& s)=0;		

		virtual void draw(){
			for (auto& ptr : list_top){
				(*ptr).daw_->draw(*ptr).			
			}		
		}
	private :
		vector<top*> list_top;


};
