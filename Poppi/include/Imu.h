#pragma once

#include <stm32f4xx_hal.h>
#include "include/stm32f4_discovery.h"
#include "include/stm32f4_discovery_accelerometer.h"
#include "include/stm32f4_discovery_gyroscope.h"

#include "include/Useful.h"

class Imu
{
public:
	Imu();
	~Imu();
	void ACCELERO_ReadAcc();
	void ACCELERO_MEMS_Test();
	void GYRO_ReadAng();
	void GYRO_MEMS_Test();

private:
	/* Init af threshold to detect acceleration on MEMS */
	int16_t ThresholdHigh;
	int16_t ThresholdLow;
};

