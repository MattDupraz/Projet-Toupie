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

	virtual double psi()const override{return 0;}
	virtual double theta()const override{return 0;}
	virtual double phi()const override{return 0;}
	virtual double d_psi()const override{return 0;}
	virtual double d_theta()const override{return 0;}
	virtual double d_phi()const override{return 0;}
	virtual double x()const override{return 0;}
	virtual double y()const override{return 0;}
	virtual double z()const override{return 0;}
	virtual double dx()const override{return 0;}
	virtual double dy()const override{return 0;}
	virtual double dz()const override{return 0;}
	virtual double getMomentInertia_xy()const override{return 0;}
	virtual double getMomentInertia_z()const override{return 0;}
	virtual double getMass()const override{return 0;}
	virtual Vector getAG()const override{return Vector {0,0,0};}
protected :
	Vector DDP_;

};


