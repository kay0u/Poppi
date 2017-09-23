#pragma once

#include <stm32f4xx_hal.h>
#include <math.h>
#include <stdio.h>

#include "BSP/stm32f411e_discovery.h"
#include "BSP/stm32f411e_discovery_accelerometer.h"
#include "BSP/stm32f411e_discovery_magnetometer.h"
#include "BSP/stm32f411e_discovery_gyroscope.h"

#include "Useful.h"
#include "Time.h"

class Imu
{
public:
	Imu();
	~Imu();

	void printAngles();
	void init();
	std::array<float, 2> getOrientation();
	std::array <float, 3> getGyroscope();
	std::array<double, 2> getAccelerometer();
	std::array <float, 3> getMagnetometer();
	float getTemperature();


private:
	void readAcc();
	void readGyr();
	void readMag();
	void computeAngles();
	float computeComplementaryfilter(float dt, float compAngle, float accelAngle, float omega);
	float formatAccelRange(float accelAngle, float accelZ);
	float formatRange0to2PI(float compAngle);
	float formatFastConverge(float compAngle, float accAngle);

	const float HPF;
	const float LPF;

	//Accelerometer
	std::array<double, 2> m_accelAngle;

	//Gyroscope
	std::array <float, 3> m_gyroValues;
	
	std::array <float, 3> m_magValues;

	//Absolute orientation
	std::array<float, 2> m_orientation;

};

