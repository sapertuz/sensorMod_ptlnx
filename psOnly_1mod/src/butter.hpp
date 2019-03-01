#ifndef BUTTER_FILT_
#define BUTTER_FILT_

#include <stdint.h>

#include "Time_Meas.h"
#include "definitions.h"

#include "definitions.h"

class butter{
public:
	butter(_real*, _real*, const _real, const _real);

	bool Filter();

	void Set_dt(uint32_t);
private:

	_real a0, b01;
	_real y_ant, x_ant;
	_real *my_y, *my_x;

	uint64_t lastTime, SampleTime;

};

#endif /* SRC_DATA_MEM_H_ */
