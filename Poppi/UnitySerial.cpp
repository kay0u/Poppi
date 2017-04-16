#include "UnitySerial.h"

#include <stdio.h>
#include <stdarg.h>

#include "Useful.h"

UnitySerial::UnitySerial()
{
}


UnitySerial::~UnitySerial()
{
}

void UnitySerial::SendAx12GoToPosition(int id, int angle)
{
#ifdef UNITY
	serial_pc::printfln("%02X%02X%02X", AX12_GOTO, id, angle);
#endif
}

void UnitySerial::SendLogToPrint(const char* format, ...)
{
#ifdef UNITY
	char buffer[256];
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	serial_pc::printfln("%02X%s", PRINT_LOG, buffer);
	va_end(args);
#endif
}