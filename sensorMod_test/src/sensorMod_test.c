#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "xil_uio.h"
#include "SensorMod.h"

#define XIL_SIZE				0x10000

#define XIL_GPIO_1_OFFSET		0x0
#define XIL_GPIO_1_TRI_OFFSET	0x4
#define XIL_GPIO_2_OFFSET		0x8
#define XIL_GPIO_2_TRI_OFFSET	0xC

const char *uio_sensorMod 	= "/dev/uio1"; // sensor mod
const char *uio_dev_0 		= "/dev/uio2"; // switches
const char *uio_dev_1 		= "/dev/uio3"; // shields leds

int main(int argc, char *argv[]) {

	printf("Start \n");

    // --------------------------------------------- Create handlers
    xil_uio *gpioSw_handler, *gpioLED_handler;
    gpioSw_handler = xil_uio__create(uio_dev_0, XIL_SIZE);
    gpioLED_handler = xil_uio__create(uio_dev_1, XIL_SIZE);

	// --------------------------------------------- Switch Read
    xil_uio__write32(gpioSw_handler, XIL_GPIO_2_TRI_OFFSET, 0xFF); // set as input
    unsigned data = xil_uio__read32(gpioSw_handler, XIL_GPIO_2_OFFSET);

	// --------------------------------------------- LED write
    xil_uio__write32(gpioLED_handler, XIL_GPIO_2_TRI_OFFSET, 0x00); // set as output
    xil_uio__write32(gpioLED_handler, XIL_GPIO_2_OFFSET, data);

    // -------------------------------------------------------
    printf("Value on Switch-LED : %d", data);

	// --------------------------------------------- Create handlers for sensorMod
    //sensorMod *sensor_handler;
    //sensor_handler = sensorMod__create(uio_sensorMod, XIL_SIZE);
    //float dt = sensorMod__get_dt(sensor_handler);
    xil_uio *sensor_handler;
    sensor_handler = xil_uio__create(uio_sensorMod, XIL_SIZE);
	unsigned int curr = xil_uio__read32(sensor_handler,	OFFSET_Q3);
    printf("\n center_current = 0x%x", curr);

    // --------------------------------------------- Destroy handlers
    xil_uio__destroy(gpioLED_handler);
    xil_uio__destroy(gpioSw_handler);

    return 0;
}

