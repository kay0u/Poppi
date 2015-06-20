#include "../include/Time.h"

const uint16_t m_daysSinceJan1[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
bool Time::leapYear(uint8_t year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

uint16_t Time::yearDay(uint8_t year, uint8_t month, uint8_t date)
{
	uint8_t yday = m_daysSinceJan1[month - 1] + date;
	if (month >= 3 && leapYear(year))
		yday += 1;
	return yday;
}

// returns the number of seconds, as an integer, since 2000-01-01
uint32_t Time::secondsSince2000(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t second)
{
	return
		second
		+ minute * 60
		+ hour * 3600
		+ (yearDay(year, month, date) - 1
		+ ((year - 2000 + 3) / 4) // add a day each 4 years starting with 2001
		- ((year - 2000 + 99) / 100) // subtract a day each 100 years starting with 2001
		+ ((year - 2000 + 399) / 400) // add a day each 400 years starting with 2001
		) * 86400
		+ (year - 2000) * 31536000;
}

uint32_t Time::getTime()
{
	RTC_DateTypeDef date;
	RTC_TimeTypeDef time;
	RTC_HandleTypeDef RTCHandle;
	HAL_RTC_GetTime(&RTCHandle, &time, FORMAT_BIN);
	HAL_RTC_GetDate(&RTCHandle, &date, FORMAT_BIN);
	printf("pouet %f\r\n", time.Seconds);
	return 0;// secondsSince2000(2000 + date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
}

Time::Time()
{
}


Time::~Time()
{
}
