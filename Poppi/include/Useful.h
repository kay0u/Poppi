#pragma once
#include "stm32f4_discovery.h"

#define ABS(x)         (x < 0) ? (-x) : x

class Useful
{
public:
	Useful();
	~Useful();

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