#ifndef KALMANPOS_V1_H
#define KALMANPOS_V1_H

#include <stdint.h>

#include "Time_Meas.h"
#include "definitions.h"

class KalmanPos
{
public:
	// Constants
#define AUTOMATIC 1
#define MANUAL 0
#define INANPIN 1
#define OUTANPIN 0

	KalmanPos(int32_t, _real*, _real*, _real*);	// Constructor

	bool Estimate();	// This funtion estimates the current estate
	void SetMode(int32_t);

	// Functions to custom the filter... These are meant to be used rigth after the constructor
	// I dont think the behavior will be correct if you set these in the middle of the filtering
	void Set_R(_real);
	void Set_nQ(_real);

	// Display Functions
	_real GetLast();

private:
	void Initialize();

	_real xp[2];
	_real a[4];
	int32_t i0;
	int32_t i1;
	int32_t i2;

	int32_t Mode;
	int32_t my_anPin;
	uint64_t my_SampleTime;
	uint64_t lastTime;
	bool inAuto;

	_real z;
	_real *my_z;
	_real my_dt;
	_real my_x[2];
	_real *my_xPos;
	_real *my_xVel;
	/*
	A = [1 dt;
	0 1]

	dt = 0.01;
	*/
	_real b_a[4] = { 1.0, 0.0, 0.01, 1.0 };
	_real b_b[4] = { 1.0, 0.01, 0.0, 1.0 };

	_real Pp[4];
	_real b;

	_real Q[4];

	/*
	P = 1*eye(2);
	*/
	_real P[4] = { 222.2222, 0, 0, 222.2222 };

	_real R = 222.2222;
	_real nQ = 7.4074e+04;

	_real K[2];
	_real b_K;

	const _real RAD_ADC = 0.0027;		// rad/ADC ->			(pi/2)/(upPos-lowPos)
};

#endif // !KALMANPOS_H
