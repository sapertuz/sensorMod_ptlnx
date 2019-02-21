#include "SensorMod.h"

//***********************************************  Constructor

// Constructor (without allocation)
void sensorMod__init(sensorMod* self, const char *_uio_dev, const uint32_t _uio_size){
    self->sensorMod_handler = xil_uio__create(_uio_dev, _uio_size);
    self->center_current._uint32 = xil_uio__read32(self->sensorMod_handler,	OFFSET_CEN_CURR);
    self->dt._uint32 = xil_uio__read32(self->sensorMod_handler, OFFSET_DT);
    self->R._uint32 = xil_uio__read32(self->sensorMod_handler, OFFSET_R);
/*
    self->Q._uint32[0] = (uint32_t *)xil_uio__read32(self->sensorMod_handler, 
                                OFFSET_CONF | OFFSET_Q0);
    self->Q._uint32[1] = (uint32_t *)xil_uio__read32(self->sensorMod_handler, 
                                OFFSET_CONF | OFFSET_Q12);
    self->Q._uint32[2] = (uint32_t *)xil_uio__read32(self->sensorMod_handler, 
                                OFFSET_CONF | OFFSET_Q3);
    self->ab._uint32[0] = (uint32_t *)xil_uio__read32(self->sensorMod_handler, 
                                OFFSET_CONF | OFFSET_a1);
    self->ab._uint32[1] = (uint32_t *)xil_uio__read32(self->sensorMod_handler, 
                                OFFSET_CONF | OFFSET_b01);
*/
}

// Allocation + initialization
sensorMod* sensorMod__create(const char *_uio_dev, const uint32_t _uio_size){
    sensorMod* result = (sensorMod*) malloc(sizeof(sensorMod));
    sensorMod__init(result, _uio_dev, _uio_size);
    return result;
}

// Destructor (without deallocation)
void  sensorMod__reset(sensorMod* self){
    xil_uio__destroy(self->sensorMod_handler);
}

// Destructor + deallocation (equivalent to "delete xil_uio")
void sensorMod__destroy(sensorMod* _sensorMod){
    if (_sensorMod) {
        sensorMod__reset(_sensorMod);
        free(_sensorMod);
    }
}

/*


//***********************************************  Calculating Functions
void sensorMod__start(sensorMod *self,
		sensorMod_data_t posIn, sensorMod_data_t currIn, sensorMod_data_t voltIn){
	//const uint8_t empty_8bit = 0;
	uint32_t data_n = 0;
	for(uint8_t mod=1; mod <= Nmodules; mod++){
		xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_POS | OFFSET_SEN | mod<<3, posIn._uint32[data_n]);
		xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_CURR | OFFSET_SEN | mod<<3, currIn._uint32[data_n]);
		xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_VOLT | OFFSET_SEN | mod<<3, voltIn._uint32[data_n]);
		data_n++;
	}
}

void sensorMod__start_float(sensorMod* self, float* posIn_f, float* currIn_f, float* voltIn_f){
	sensorMod_data_t posIn, currIn, voltIn;
    posIn._float32 = posIn_f;   currIn._float32 = currIn_f;   voltIn._float32 = voltIn_f;   
    sensorMod__start(self, posIn, currIn, voltIn);
}

uint32_t sensorMod__isReady(sensorMod* self){
    uint32_t status = xil_uio__read32(self, STATUS_READ);
    if ( (status|READY_MASK)>>16 == ISREADY ){
        return 1;
    }else{
        return 0;
    }
}

void sensorMod__get_filteredData(sensorMod* self){
    while(~sensorMod__isReady(self));
    
}
//float *sensorMod_get_filteredData(sensorMod* self);

//***********************************************  Configuration Functions
void sensorMod__set_centerCurr(sensorMod* self, float centerCurr){
    self->center_current._float32 = &centerCurr;
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_CEN_CURR | OFFSET_CONF, (uint32_t *)self->center_current._uint32);
}

void sensorMod__set_Kalman(sensorMod* self, float dt, float R, float nQ){
    self->dt._float32 = &dt;
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_DT | OFFSET_CONF, (uint32_t *)self->dt._uint32);
    self->R._float32 = &R;
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_R | OFFSET_CONF, (uint32_t *)self->R._uint32);

    self->Q._float32[0] = (nQ*dt*dt*dt*dt)/4.0f;    // (nQ*dt^4)/4
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_Q0 | OFFSET_CONF, self->Q._uint32[0]);
    self->Q._float32[1] = (nQ*dt*dt*dt)/2.0f;       // (nQ*dt^3)/2 
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_Q12 | OFFSET_CONF, self->Q._uint32[1]);
    self->Q._float32[2] = nQ*dt;                    // nQ*dt 
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_Q3 | OFFSET_CONF, self->Q._uint32[2]);
}

void sensorMod__set_butter(sensorMod* self, float* ab){
    self->ab._float32[0] = ab[0];
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_a1 | OFFSET_CONF, self->ab._uint32[0]);
    self->ab._float32[1] = ab[1];
    xil_uio__write32(self->sensorMod_handler->virtAddr,
			OFFSET_b01 | OFFSET_CONF, self->ab._uint32[1]);
}

//***********************************************  Variable Functions
float sensorMod__get_centerCurr(sensorMod* self){return (float)*self->center_current._float32;}
float sensorMod__get_dt(sensorMod* self){return (float)*self->dt._float32;};
float sensorMod__get_R(sensorMod* self){return (float)*self->R._float32;};
float* sensorMod__get_Q(sensorMod* self){return (float *)self->Q._float32;};
float* sensorMod__get_ab(sensorMod* self){return (float *)self->ab._float32;};

*/
