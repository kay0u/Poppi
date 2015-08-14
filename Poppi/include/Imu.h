#pragma once

#include <stm32f4xx_hal.h>
#include <math.h>
#include <stdio.h>

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
	void init();
	float* getOrientation();

private:
	void readAcc();
	void readGyr();
	void computeAngles();
	float computeComplementaryfilter(float dt, float compAngle, float accelAngle, float omega);
	float formatAccelRange(float accelAngle, float accelZ);
	float formatRange0to2PI(float compAngle);
	float formatFastConverge(float compAngle, float accAngle);

	const float HPF;
	const float LPF;

	//Accelerometer
	double m_accelAngle[2];

	//Gyroscope
	float m_gyroValues[3];

	//Absolute orientation
	float m_orientation[2];
};

