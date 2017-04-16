#pragma once

#include <string>

#define UNITY

class UnitySerial
{
	enum {
		PRINT_LOG = 0x00,
		AX12_GOTO = 0x01
	};
	
public:
	UnitySerial();
	~UnitySerial();
	
	static void SendAx12GoToPosition(int id, int angle);
	static void SendLogToPrint(const char* format, ...);
};

