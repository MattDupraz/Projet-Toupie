#pragma once
#include "top.h"


class TopTestSine : public TopTestFall{
public:
	TopTestSine(std::shared_ptr<View> v, Vector const& P, Vector const& DP, Vector const& DDP)
	:TopTestFall(v,P,DP,DDP){}

	virtual Vector getDDP(Vector P, Vector DP)override{return -P_;}
	
};
