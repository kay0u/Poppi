#pragma once

#include <stm32f4xx_hal.h>
#include <math.h>

#include "stm32f4_discovery.h"
#include "stm32f4_discovery_accelerometer.h"
#include "stm32f4_discovery_gyroscope.h"

#include "Useful.h"
#include "Time.h"

class Imu
{
public:
	Imu();
	~Imu();

	void printAngles();

private:
	void readAcc();
	void readGyr();
	void computeAngles();
	void computeOneAngle(uint8_t dt, int id);

	const float HPF;
	const float LPF;

	//Accelerometer
	double m_accelAngle[2];

	//Gyroscope
	float m_gyroValues[3];
	float m_gyroOffset[2];
	float m_gyroTotal[2];

	//Time
	uint32_t previousFrameTime;

	//Absolute orientation
	double m_orientation[2];
};

