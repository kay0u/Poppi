#pragma once


#define UNITY

class UnitySerial
{
	enum {
		AX12_GOTO = 0x01
	};
	
public:
	UnitySerial();
	~UnitySerial();
	
	static void SendAx12GoToPosition(int id, int angle);
};

