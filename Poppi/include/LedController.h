/*
 * LedController.h
 *
 *  Created on: 10 janv. 2016
 *      Author: Vincent
 */

#ifndef LEDCONTROLLER_H_
#define LEDCONTROLLER_H_

#include <BSP/stm32f411e_discovery.h>
#include "cmsis_os.h"

typedef enum  {
	LedBlue = LED6,
	LedOrange = LED3,
	LedGreen = LED4,
	LedRed = LED5
} LedColor;

class LedController {
public:
	static LedController& Instance();
	void ledOff(Led_TypeDef led);
	void ledOn(Led_TypeDef led);
	void toggleLed(Led_TypeDef led);
	void ledOff(LedColor led);
	void ledOn(LedColor led);
	void toggleLed(LedColor led);
	void allLedOff();
	void allLedOn();
	void toggleAllLed();

	LedController(LedController const&) = delete;             // Copy construct
	LedController(LedController&&) = delete;                  // Move construct
	LedController& operator=(LedController const&) = delete;  // Copy assign
	LedController& operator=(LedController &&) = delete;      // Move assign
private:
	LedController();
	virtual ~LedController();
	osMutexId m_mutexId;
};

#endif /* LEDCONTROLLER_H_ */
