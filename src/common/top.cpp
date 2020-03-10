#include "top.h"

#include <iostream>

void Top::update(double dt) {
	pos_ += vel_ * dt;
	angPos_ += angVel_ * dt;

	//update angVel and vel;
}
