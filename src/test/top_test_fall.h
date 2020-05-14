#pragma once
#include "top.h"

class TopTestFall : public Top{
public:
	TopTestFall(std::shared_ptr<View> v, Vector const& P, Vector const& DP, Vector const& DDP)
	:Top(v,P,DP), DDP_(DDP){}

	void setP(Vector const& DDP) { DDP_ = DDP; }

	virtual void draw()const{;}

	virtual Vector getDDP(Vector P, Vector DP)override{return DDP_;}
	virtual std::ostream& print(std::ostream& os)const override{
		os << P_ << " " << DP_;
		return os;}

	virtual double getEnergy()const override{return 0;}
	virtual double getL_Ak()const override{return 0;}
	virtual double getL_Aa()const override{return 0;}

protected :
	Vector DDP_;

};


