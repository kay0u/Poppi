#include "UnitySerial.h"

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