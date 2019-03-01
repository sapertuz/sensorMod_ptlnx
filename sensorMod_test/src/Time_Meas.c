/*
 * Time_Meas.c
 *
 *  Created on: 27 de fev de 2019
 *      Author: sapmc
 */

#include "Time_Meas.h"

struct timespec tp;

uint64_t millis(){
	clock_gettime(CLOCK_MONOTONIC, &tp);
	uint64_t  x_time = tp.tv_nsec;

	x_time = x_time / CLOCKS_PER_SEC;

	return (uint64_t)x_time;
}
