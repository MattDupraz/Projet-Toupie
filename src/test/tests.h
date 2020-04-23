#pragma once
#include "top.h"

class Tests {
	public:
		void testVector();
		void testMatrix3x3();
		void testTop();
		void testIntegration();
};



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

protected :
	Vector DDP_;

};

class TopTestSine : public TopTestFall{
public:
	TopTestSine(std::shared_ptr<View> v, Vector const& P, Vector const& DP, Vector const& DDP)
	:TopTestFall(v,P,DP,DDP){}

	virtual Vector getDDP(Vector P, Vector DP)override{return -P_;}
	




};
