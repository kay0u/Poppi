#pragma once
#include <stdio.h>
#include <stdarg.h>

#include "LedController.h"
#include <BSP/stm32f411e_discovery.h>
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "src/Uart.hpp"

#define LEG_COUNT 6
#define TWO_PI  6.2831853f
#define HALF_PI 1.5707963f
#define ABS(x)  (x < 0) ? (-x) : x
#define SQRE(x) ((x)*(x))

using serial_pc = Uart<1>;
using serial_ax = Uart<2>;

// Converts degrees to radians.
#define DEGREETORADIAN(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define RADIANTODEGREE(angleRadians) (angleRadians * 180.0 / M_PI)

extern int printDebug(const char *fmt, ...);
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
