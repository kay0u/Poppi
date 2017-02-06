#include "Imu.h"
#include "inttypes.h"

#define M_PI		3.14159265358979323846

Imu::Imu() :
HPF(0.98f),
LPF(0.02),
m_orientation()
{
}
#undef DEBUG

/**
 * @brief  Initialize the accelerometer and the gyroscope.
 * @param  None
 * @retval None
 */
void Imu::init()
{
	if (BSP_ACCELERO_Init() != HAL_OK)
	{
#ifdef DEBUG
		printf("[IMU]Error encountered while initializeing the accelerometer : %" PRIu8 "\r\n", BSP_ACCELERO_Init());
#endif
	}
	if (BSP_GYRO_Init() != HAL_OK)
	{
#ifdef DEBUG
		printf("[IMU]Error encountered while initializeing the gyroscope.\r\n");
#endif
	}
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
 * @brief  Read Gyroscope Angular data.
 * @param  None
 * @retval None
 */
void Imu::readGyr()
{
	BSP_GYRO_GetXYZ(m_gyroValues);
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
		accelAngle = TWO_PI + accelAngle; // Angle lies in Quadrant 4 of the unit circle

	return accelAngle;
}

float* Imu::getOrientation() {
	computeAngles();
	return m_orientation;
}

float* Imu::getGyroscope()
{
	readGyr();
	return m_gyroValues;
}

double* Imu::getAccelerometer()
{
	readAcc();
	return m_accelAngle;
}

/**
 * @brief  Significantly increases complementary convergence speed
 * @param  compAngle the computed angle
 * @param  accAngle the formated angle currently mesured by the accelerometer
 * @retval another value for  the computed angle
 */
float Imu::formatFastConverge(float compAngle, float accAngle)
{
	if (compAngle > accAngle + M_PI)
		compAngle = compAngle - TWO_PI;
	else if (accAngle > compAngle + M_PI)
		compAngle = compAngle + TWO_PI;
	return compAngle;
}

/**
 * @brief  Format the computed angle to lie in the range [0, 2*PI]
 * @param  compAngle the computed angle
 * @retval the formated angle
 */
float Imu::formatRange0to2PI(float compAngle)
{
	while (compAngle >= TWO_PI)
		compAngle = compAngle - TWO_PI;
	while (compAngle < 0.0f)
		compAngle = compAngle + TWO_PI;
	return compAngle;
}

/**
 * @brief  Update the values from the accelerometer and gyroscope and compute the aboslute
 *		  angle using a complementary filter. The result lies in m_orientation.
 * @param  None
 * @retval None
 */
void Imu::computeAngles()
{
	//Update the accelerometer and gyroscope values
	readAcc();
	readGyr();

	float dt = 0.01f;

	//Compute X and Y separatly
	m_orientation[0] = computeComplementaryfilter(dt, m_orientation[0], m_accelAngle[0], m_gyroValues[0]);
	m_orientation[1] = computeComplementaryfilter(dt, m_orientation[1], m_accelAngle[1], m_gyroValues[1]);
}

/**
 * @brief  Apply the complementary filter on one angle
 * @param  dt delta time
 * @param  compAngle previously computed angle
 * @param  accelAngle current accelerometer angle
 * @param  gyroValue current gyroscope value
 * @retval The computed angle
 */
float Imu::computeComplementaryfilter(float dt, float compAngle, float accelAngle, float gyroValue)
{
	// Speed up filter convergence
	compAngle = formatFastConverge(compAngle, accelAngle);

	// Integrate the gyroscope's angular velocity reading to get an angle
	float gyroAngle = compAngle + gyroValue*dt;

	// Weight the accelerometer and gyroscope values and put them together
	compAngle = LPF * gyroAngle + HPF*accelAngle;

	// Format the computed angle
	compAngle = formatRange0to2PI(compAngle);

	return compAngle;
}

/**
 * @brief  Debug function that prints the angles computed by the complementary filter.
 * @param  None
 * @retval None
 */
void Imu::printAngles()
{
	computeAngles();
#ifdef DEBUG
	printf("%f %f\r\n", m_orientation[0], m_orientation[1]);
#endif
}
