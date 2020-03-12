#include "top.h"
#include "vect.h"
#include "view.h"

void Top::update(double dt) {
	pos_ += vel_*dt;
	angPos_ += angVel_*dt;
}
