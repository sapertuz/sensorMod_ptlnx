#ifndef KALMANPOS_V1_H
#define KALMANPOS_V1_H

#include "Time_Meas.h"

class KalmanPos
{
public:
	// Constants
#define AUTOMATIC 1
#define MANUAL 0
#define INANPIN 1
#define OUTANPIN 0

	KalmanPos(int, double*, double*);	// Constructor

	bool Estimate();	// This funtion estimates the current estate
	void SetMode(int);

	// Functions to custom the filter... These are meant to be used rigth after the constructor
	// I dont think the behavior will be correct if you set these in the middle of the filtering
	void Set_R(double);
	void Set_nQ(double);

	// Display Functions
	double GetLast();

private:
	void Initialize();

	double xp[2];
	double a[4];
	int i0;
	int i1;
	int i2;

	int Mode;
	int my_anPin;
	unsigned int my_SampleTime;
	unsigned long lastTime;
	bool inAuto;

	double z;
	double *my_z;
	double my_dt;
	double *my_x;
	/*
	A = [1 dt;
	0 1]

	dt = 0.01;
	*/
	double b_a[4] = { 1.0, 0.0, 0.01, 1.0 };
	double b_b[4] = { 1.0, 0.01, 0.0, 1.0 };

	double Pp[4];
	double b;

	double Q[4];

	/*
	P = 1*eye(2);
	*/
	double P[4] = { 222.2222, 0, 0, 222.2222 };

	double R = 222.2222;
	double nQ = 7.4074e+04;

	double K[2];
	double b_K;

	const double RAD_ADC = 0.0027;		// rad/ADC ->			(pi/2)/(upPos-lowPos)
};

#endif // !KALMANPOS_H
