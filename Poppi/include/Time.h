#pragma once
#include <stdio.h>

#include "BSP/stm32f411e_discovery.h"

#ifdef __cplusplus
class Time
{
public:
	Time();
	~Time();

	static uint32_t getTime();

private:
	static uint32_t secondsSince2000(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second);
	static bool leapYear(uint8_t year);
	static uint16_t yearDay(uint8_t year, uint8_t month, uint8_t date);
};
#endif
