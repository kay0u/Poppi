/*
 * LedController.cpp
 *
 *  Created on: 10 janv. 2016
 *      Author: Vincent
 */

#include "LedController.h"

LedController::LedController()
{
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);
	osMutexDef(osMutex);
	m_mutexId = osMutexCreate(osMutex(osMutex));
}

LedController::~LedController()
{

}

LedController& LedController::Instance()
{	static LedController instance;
	return instance;
}

void LedController::ledOff(Led_TypeDef led)
{
	osMutexWait(m_mutexId, 0);
	BSP_LED_Off(led);
	osMutexRelease(m_mutexId);
}

void LedController::ledOn(Led_TypeDef led)
{
	osMutexWait(m_mutexId, 0);
	BSP_LED_On(led);
	osMutexRelease(m_mutexId);
}

void LedController::toggleLed(Led_TypeDef led)
{
	osMutexWait(m_mutexId, 0);
	BSP_LED_Toggle(led);
	osMutexRelease(m_mutexId);
}


void LedController::ledOff(LedColor led)
{
	ledOff((Led_TypeDef)led);
}

void LedController::ledOn(LedColor led)
{
	ledOn((Led_TypeDef)led);
}

void LedController::toggleLed(LedColor led)
{
	toggleLed((Led_TypeDef)led);
}

void LedController::toggleAllLed()
{
	toggleLed(LED3);
	toggleLed(LED4);
	toggleLed(LED5);
	toggleLed(LED6);
}

void LedController::allLedOff()
{
	ledOff(LED3);
	ledOff(LED4);
	ledOff(LED5);
	ledOff(LED6);
}

void LedController::allLedOn()
{
	ledOn(LED3);
	ledOn(LED4);
	ledOn(LED5);
	ledOn(LED6);
}
