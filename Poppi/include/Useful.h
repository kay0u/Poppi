#pragma once
#include "stm32f4_discovery.h"
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h"

#define TWO_PI  6.2831853f
#define HALF_PI 1.5707963f
#define ABS(x)  (x < 0) ? (-x) : x
#define SQRE(x) ((x)*(x))

//Set to false to hide logs
#define DEBUG true

// Converts degrees to radians.
#define DEGREETORADIAN(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define RADIANTODEGREE(angleRadians) (angleRadians * 180.0 / M_PI)

class Useful
{
public:
	Useful();
	~Useful();

	static int16_t distance(int16_t d1, int16_t d2);

	static uint8_t UserPressButton;
};


#ifdef __cplusplus
extern "C"
{
#endif
	/* Exported types ------------------------------------------------------------*/
	/* Exported constants --------------------------------------------------------*/
	/* Exported macro ------------------------------------------------------------*/

	void Error_Handler(void);
#ifdef __cplusplus
}
#endif