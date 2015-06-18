#pragma once

#include <stm32f4xx_hal.h>
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_accelerometer.h"
#include "stm32f4_discovery_gyroscope.h"

#include "Useful.h"

class Imu
{
public:
	Imu();
	~Imu();

	void printAngles();
	void comp_filter(float newAngle, float newRate);

private:
	void ACCELERO_ReadAcc();
	void GYRO_ReadAng();

	/* Init af threshold to detect acceleration on MEMS */
	int16_t ThresholdHigh;
	int16_t ThresholdLow;

	int16_t xAccel;
	int16_t yAccel;
	float xGyro;
	float yGyro;

	float xAngleFiltered;
	float dt = 0.02;
};

