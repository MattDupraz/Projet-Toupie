#pragma once
#include "top.h"

// Toupie test "sinus"
// C'est un peu bricolé pour que ça marche, car ça ne rentre pas
// dans la conception du projet
class TopTestSine : public TopTestFall{
public:
	TopTestSine(std::shared_ptr<View> v, Vector const& P, Vector const& DP, Vector const& DDP)
		:TopTestFall(v,P,DP,DDP){}

	virtual Vector getDDP(Vector P, Vector DP) override {
		return -P_;
	}
	
};
