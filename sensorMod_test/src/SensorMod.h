#ifndef SENSORMOD_H
#define SENSORMOD_H

/****************** Include Files ********************/

#include "xil_uio.h"
#include "Time_Meas.h"

#define SENMOD_SIZE		0x10000
/*
#define OFFSET_POS      0x02
#define OFFSET_CURR     0x04
#define OFFSET_VOLT     0x06

#define OFFSET_POS_F    0x02
#define OFFSET_VEL_F    0x04
#define OFFSET_CURR_F   0x06

#define OFFSET_DT       0x00
#define OFFSET_R        0x08
#define OFFSET_CEN_CURR 0x16
#define OFFSET_Q0       0x18
#define OFFSET_Q12      0x20
#define OFFSET_Q3       0x28
#define OFFSET_b01      0x30
#define OFFSET_a1       0x38

#define OFFSET_FILT     0x00
#define OFFSET_SEN      0x40
#define OFFSET_CONF     0x80
*/

#define STATUS_R_MOD_W 		0
#define OFFSET_DT 			4
#define OFFSET_R 			8
#define OFFSET_CEN_CURR 	12
#define OFFSET_Q0 			16
#define OFFSET_Q12 			20
#define OFFSET_Q3 			24
#define OFFSET_b01 			28
#define OFFSET_a1 			32

#define OFFSET_POS 			36
#define OFFSET_VEL_CURR		40
#define OFFSET_CURR_VOLT 	44

#define Nmodules			7

//#define STATUS_READ     0x01
#define READY_MASK		0xFFFF0000
//#define ISREADY			(1<<Nmodules)-1
#define MASK_MOD_IN		0xFFFFFFE0
#define MASK_READY		0xFFFF0000
#define ISREADY			0x7F0000

/**************************** Type Definitions *****************************/
typedef union sensorMod_union_t {
	        uint32_t 	*_uint32;
	        float 		*_float32;
        }sensorMod_data_t;

typedef struct sensorMod_struct{
	xil_uio *sensorMod_handler;

	sensorMod_data_t filt_pos, filt_vel, filt_curr;
	sensorMod_data_t posIn, currIn, voltIn;

	sensorMod_data_t center_current;
	sensorMod_data_t dt, R, Q;
	sensorMod_data_t ab;

	uint64_t lastTime;
	uint64_t SampleTime;
}sensorMod;

/************************** Driver Class Definition ************************/

//***********************************************  Constructor
sensorMod* sensorMod__create(const char *_uio_dev, const uint32_t _uio_size, 
	float* posIn, float* currIn, float* voltIn,
	float* pos_filt, float* vel_filt, float* curr_filt);
void sensorMod__destroy(sensorMod* self);



//***********************************************  Calculating Functions
void sensorMod__reset(sensorMod* self);
void sensorMod__start(sensorMod* self);
void sensorMod__wait(sensorMod* self);
void sensorMod__get_modFilt_Data(sensorMod* self, uint32_t mod, float* mod_data);

//***********************************************  Configuration Functions
void sensorMod__set_centerCurr(sensorMod* self, const float centerCurr);
void sensorMod__set_Kalman(sensorMod* self, float dt, float R, float Q);
void sensorMod__set_butter(sensorMod* self, float* ab);

//***********************************************  Variable Functions
float sensorMod__get_centerCurr(sensorMod* self);
float sensorMod__get_dt(sensorMod* self);
float sensorMod__get_R(sensorMod* self);
float* sensorMod__get_Q(sensorMod* self);
float* sensorMod__get_ab(sensorMod* self);

void sensorMod__printConfig(sensorMod* self);

#endif // SENSORMOD_H
