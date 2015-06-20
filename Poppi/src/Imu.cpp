#include "../include/Imu.h"
#include "inttypes.h"

Imu::Imu() :
	HPF(0.98f),
	LPF(0.02)
{
	if (BSP_ACCELERO_Init() != HAL_OK || BSP_ACCELERO_Init() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	m_gyroOffset[0] = m_gyroOffset[1] = 0;
	//previousFrameTime = Time::getTime();
}


Imu::~Imu()
{
}

/**
* @brief  Read acceleration data and format the data in angles in [0, 2*pi].
* @param  None
* @retval None
*/
void Imu::readAcc()
{
	// Read Acceleration
	int16_t accelValues[3] = { 0 };
	BSP_ACCELERO_GetXYZ(accelValues);

	// Angle made by X axis acceleration vector relative to ground
	m_accelAngle[0] = atan2f(accelValues[0], sqrt(SQRE(accelValues[1]) + SQRE(accelValues[2])));
	// Angle made by Y axis acceleration vector relative to ground
	m_accelAngle[1] = atan2f(accelValues[1], sqrt(SQRE(accelValues[0]) + SQRE(accelValues[2])));

	//Format angles
	m_accelAngle[0] = formatAccelRange(m_accelAngle[0], accelValues[2]);
	m_accelAngle[1] = formatAccelRange(m_accelAngle[1], accelValues[2]);
}

/**
* @brief  Find the quarant whee the angle lies and format it in range [0, 2*pi]
* @param  accelAngle the angle (float)
* @param  accelZ the raw Z acceleration (float)
* @retval The formated angle.
*/
float Imu::formatAccelRange(float accelAngle, float accelZ)
{
	if (accelZ < 0.0f)
		accelAngle = M_PI - accelAngle; // Angle lies in Quadrant 2 or Quadrant 3 of the unit circle
	else if (accelZ > 0.0f && accelAngle < 0.0f)
		accelAngle = 2 * M_PI + accelAngle; // Angle lies in Quadrant 4 of the unit circle

	return accelAngle;
}

/**
* @brief  Read Gyroscope Angular data.
* @param  None
* @retval None
*/
void Imu::readGyr()
{
	/* Read Gyroscope Angular data */
	BSP_GYRO_GetXYZ(m_gyroValues);
}

void Imu::computeAngles()
{
	///Compute delta time
	/*uint32_t currentTime = Time::getTime();
	uint8_t dt = previousFrameTime - currentTime;
	previousFrameTime = currentTime;*/
	float dt = 0.1f;

	//Update the accelerometer and gyroscope values
	readAcc();
	readGyr();

	//Compute X and Y separatly
	computeOneAngle(dt, 0);
	computeOneAngle(dt, 1);
}

void Imu::computeOneAngle(uint8_t dt, int id)
{
	m_gyroValues[id] -= m_gyroOffset[id];
	float delta = m_gyroValues[id] * dt;
	m_gyroTotal[id] += delta;

	m_orientation[id] = HPF * (m_orientation[0] + delta) + (LPF * m_accelAngle[id]);
}

void Imu::printAngles()
{
	computeAngles();
}