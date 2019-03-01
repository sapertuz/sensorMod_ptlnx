#include "butter.hpp"

butter::butter(_real *x, _real *y, _real a, _real b){
	this->my_x = x;
	this->my_y = y;

	this->a0 = a;
	this->b01 = b;

	this->y_ant = 0;

	this->SampleTime = 5;
	this->lastTime = millis();
}

bool butter::Filter(){
	uint64_t now = millis();
	uint64_t timeChange = (now - lastTime);
	if (timeChange >= SampleTime) {
		_real x, y;
		x = *my_x;
		y = x*b01 + x_ant*b01 - y_ant*a0;
		my_y = &y;

		x_ant = x;
		y_ant = y;

		lastTime = now;
		return true;
	}else{
		return false;
	}
}

void butter::Set_dt(uint32_t dt){
	SampleTime = dt;
}
