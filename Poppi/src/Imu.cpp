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
* @brief  Read Acceleration data.
* @param  None
* @retval None
*/
void Imu::readAcc()
{
	/* Read Acceleration */
	int16_t m_accelValues[3] = { 0 };
	BSP_ACCELERO_GetXYZ(m_accelValues);
	printf("%" PRId16 " %" PRId16 "\r\n", m_accelValues[0], m_accelValues[1]);
	m_accelAngle[0] = RADIANTODEGREE(atan2(m_accelValues[0], Useful::distance(m_accelValues[1], m_accelValues[2])));
	m_accelAngle[1] = RADIANTODEGREE(atan2(m_accelValues[1], Useful::distance(m_accelValues[0], m_accelValues[2])));
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