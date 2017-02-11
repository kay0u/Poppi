#include "AX12.h"
#include "cmsis_os.h"
#include <algorithm>
#include <cmath>
#include "Useful.h"

template<typename serial>
AX12<serial>::AX12()
{
}


template<typename serial>
AX12<serial>::~AX12()
{
}


template<typename serial>
AX12<serial>::AX12(int ID, int baud)
{
	_ID = ID;
	_baud = baud;
	_mode = Mode::Join;
	serial::init(baud);
	serial::changeCommunicationMode(serial::communicationMode::TX);
	SetMode(_mode);
}

template<typename serial>
void AX12<serial>::SetMode(Mode mode) {

	_mode = mode;
	
	switch (mode)
	{
	case Mode::Wheel:
		SetClockwiseLimit(0);
		SetCounterClockwiseLimit(0);
		SetSpeed(0);
		break;
	case Mode::Join:
	default:
		SetClockwiseLimit(0);
		SetCounterClockwiseLimit(300);
		SetSpeed(1);
		break;
	}
}


template<typename serial>
int  AX12<serial>::SetBaudrate(int baud) {

	//TODO: check
	int flag = 0;
	char data[1];
	data[0] = baud;

#ifdef AX12_DEBUG
	printf("Setting Baud rate to %d\n", baud);
#endif

	return (write(0xFE, AX12_REG_BAUD, 1, data, flag));
}


template<typename serial>
int AX12<serial>::SetGoal(int degrees, int flags) {

	char reg_flag = 0;
	char data[2];

	// set the flag is only the register bit is set in the flag
	if (flags == 0x2) {
		reg_flag = 1;
	}

	// 1023 / 300 * degrees
	short goal = (1023 * degrees) / 300;
#ifdef AX12_DEBUG
	printf("SetGoal to 0x%x\n", goal);
#endif

	data[0] = goal & 0xff; // bottom 8 bits
	data[1] = goal >> 8;   // top 8 bits

	// write the packet, return the error code
	int rVal = write(_ID, AX12_REG_GOAL_POSITION, 2, data, reg_flag);
#ifdef UNITY
	Uart<1>::printfln("AX12 move %d %d", _ID, degrees);
#endif
	if (flags == 1) {
	// block until it comes to a halt
		while (isMoving()) {}
	}
	return (rVal);
}


template<typename serial>
int AX12<serial>::SetSpeed(float speed) {

	//TODO: check
	int flag = 0;

	// bit 10     = direction, 0 = CCW, 1=CW //If in Wheel mode
	// bits 9-0   = Speed
	char data[2];

	int goal = (0x3ff * std::abs(speed));

		// Set direction CW if we have a negative speed
	if ((_mode == Mode::Wheel) && (speed < 0))
		goal |= (0x1 << 10);

	data[0] = goal & 0xff; // bottom 8 bits
	data[1] = goal >> 8;   // top 8 bits

	// write the packet, return the error code
	int rVal = write(_ID, AX12_REG_MOVING_SPEED, 2, data, flag);

	return (rVal);
}


template<typename serial>
int AX12<serial>::SetClockwiseLimit(int degrees) {

	//TODO: check
	int flag = 0;

	degrees = std::max(degrees, 0);
	degrees = std::min(degrees, 300);
		
	char data[2];

	// 1023 / 300 * degrees
	short limit = (1023 * degrees) / 300;

#ifdef AX12_DEBUG
	printf("SetCWLimit to 0x%x\n", limit);
#endif

	data[0] = limit & 0xff; // bottom 8 bits
	data[1] = limit >> 8;   // top 8 bits

	// write the packet, return the error code
	return (write(_ID, AX12_REG_CW_LIMIT, 2, data, flag));

}

template<typename serial>
int AX12<serial>::SetCounterClockwiseLimit(int degrees) {

	//TODO: check
	int flag = 0;

	degrees = std::max(degrees, 0);
	degrees = std::min(degrees, 300);
		
	char data[2];

	// 1023 / 300 * degrees
	short limit = (1023 * degrees) / 300;

#ifdef AX12_DEBUG
	printf("SetCCWLimit to 0x%x\n", limit);
#endif

	data[0] = limit & 0xff; // bottom 8 bits
	data[1] = limit >> 8;   // top 8 bits

	// write the packet, return the error code
	return (write(_ID, AX12_REG_CCW_LIMIT, 2, data, flag));
}

template<typename serial>
int AX12<serial>::SetID(int currentID, int newID) {

	//TODO: check
	int flag = 0;

	char data[1];
	data[0] = newID;

#ifdef AX12_DEBUG
	printf("Setting ID from 0x%x to 0x%x\n", currentID, newID);
#endif
	_ID = newID;
	//TODO: catch error
	return (write(currentID, AX12_REG_ID, 1, data, flag));

}


template<typename serial>
bool AX12<serial>::isMoving() {

	char data[1];
	read(_ID, AX12_REG_MOVING, 1, data);
	return (data[0] == 1);
}

template<typename serial>
void AX12<serial>::trigger() {

	char TxBuf[16];
	char sum = 0;

#ifdef AX12_TRIGGER_DEBUG
	// Build the TxPacket first in RAM, then we'll send in one go
	printf("\nTriggered\n");
	printf("\nTrigger Packet\n  Header : 0xFF, 0xFF\n");
#endif

	TxBuf[0] = 0xFF;
	TxBuf[1] = 0xFF;

	// ID - Broadcast
	TxBuf[2] = 0xFE;
	sum += TxBuf[2];

#ifdef AX12_TRIGGER_DEBUG
	printf("  ID : %d\n", TxBuf[2]);
#endif

	// Length
	TxBuf[3] = 0x02;
	sum += TxBuf[3];

#ifdef AX12_TRIGGER_DEBUG
	printf("  Length %d\n", TxBuf[3]);
#endif

	// Instruction - ACTION
	TxBuf[4] = 0x04;
	sum += TxBuf[4];

#ifdef AX12_TRIGGER_DEBUG
	printf("  Instruction 0x%X\n", TxBuf[4]);
#endif

	// Checksum
	TxBuf[5] = 0xFF - sum;
#ifdef AX12_TRIGGER_DEBUG
	printf("  Checksum 0x%X\n", TxBuf[5]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::print(TxBuf, 6);

	// This is a broadcast packet, so there will be no reply
	return;
}

template<typename serial>
float AX12<serial>::GetPosition() {

#ifdef AX12_DEBUG
	printf("\nGetPosition(%d)", _ID);
#endif

	char data[2];

	int ErrorCode = read(_ID, AX12_REG_POSITION, 2, data);
	int position = data[0] + (data[1] << 8);
	float angle = (position * 300) / 1024;

	return (angle);
}
	
template<typename serial>
float AX12<serial>::GetSpeed() {

#ifdef AX12_DEBUG
	printf("\nGetPosition(%d)", _ID);
#endif

	char data[2];

	int ErrorCode = read(_ID, AX12_REG_SPEED, 2, data);

	int speed = data[0] + (0x03 & data[1] << 8);
	if (data[1] & 0x07)
		speed *= -1;
	
	return speed;
}

template<typename serial>
float AX12<serial>::GetTemp() {

#ifdef AX12_DEBUG
	printf("\nGetTemp(%d)", _ID);
#endif

	char data[1];
	int ErrorCode = read(_ID, AX12_REG_TEMP, 1, data);
	float temp = data[0];
	return temp;
}

	/** Read the supply voltage of the servo
	*
	* @returns float voltage
	*/
template<typename serial>
float AX12<serial>::GetVolts() {

#ifdef AX12_DEBUG
	printf("\nGetVolts(%d)", _ID);
#endif

	char data[1];
	int ErrorCode = read(_ID, AX12_REG_VOLTS, 1, data);
	float volts = data[0] / 10.0;
	return (volts);
}

template<typename serial>
int AX12<serial>::read(int ID, int start, int bytes, char* data) {

	char PacketLength = 0x4;
	char TxBuf[16];
	char sum = 0;
	char Status[16];

	Status[4] = 0xFE; // return code

#ifdef AX12_READ_DEBUG
	serial_pc::printf("\nread(%d,0x%x,%d,data)\n", ID, start, bytes);
#endif

	// Build the TxPacket first in RAM, then we'll send in one go
#ifdef AX12_READ_DEBUG
	serial_pc::printf("\nInstruction Packet\n  Header : 0xFF, 0xFF\n");
#endif

	TxBuf[0] = 0xff;
	TxBuf[1] = 0xff;

	// ID
	TxBuf[2] = ID;
	sum += TxBuf[2];

#ifdef AX12_READ_DEBUG
	serial_pc::printf("  ID : %d\n", TxBuf[2]);
#endif

	// Packet Length
	TxBuf[3] = PacketLength;    // Length = 4 ; 2 + 1 (start) = 1 (bytes)
	sum += TxBuf[3];            // Accululate the packet sum

#ifdef AX12_READ_DEBUG
	serial_pc::printf("  Length : 0x%x\n", TxBuf[3]);
#endif

	// Instruction - Read
	TxBuf[4] = 0x2;
	sum += TxBuf[4];

#ifdef AX12_READ_DEBUG
	serial_pc::printf("  Instruction : 0x%x\n", TxBuf[4]);
#endif

	// Start Address
	TxBuf[5] = start;
	sum += TxBuf[5];

#ifdef AX12_READ_DEBUG
	serial_pc::printf("  Start Address : 0x%x\n", TxBuf[5]);
#endif

	// Bytes to read
	TxBuf[6] = bytes;
	sum += TxBuf[6];

#ifdef AX12_READ_DEBUG
	serial_pc::printf("  No bytes : 0x%x\n", TxBuf[6]);
#endif

	// Checksum
	TxBuf[7] = 0xFF - sum;
#ifdef AX12_READ_DEBUG
	serial_pc::printf("  Checksum : 0x%x\n", TxBuf[7]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(TxBuf, 8);
		
	serial::lockMutex();
		
	// Wait for the bytes to be transmitted
	osDelay((6 + bytes) * 1000.0 / _baud);

	// Skip if the read was to the broadcast address
	if (_ID != 0xFE) {

		serial::changeCommunicationMode(serial::communicationMode::RX);


		// response packet is always 6 + bytes
		// 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
		// timeout is a little more than the time to transmit
		// the packet back, i.e. (6+bytes)*10 bit periods

		int timeout = 0;
		int plen = 0;
		while ((timeout < ((6 + bytes) * 10)) && (plen < (6 + bytes))) {

			if (serial::available()) {
				serial::releaseMutex();
				serial::read_char(Status[plen]);
				serial::lockMutex();
				plen++;
				timeout = 0;
			}

			// wait for the bit period
			osDelay(1000.0 / _baud);
			timeout++;
		}
		serial::releaseMutex();
			
		serial::changeCommunicationMode(serial::communicationMode::TX);

		if (timeout == ((6 + bytes) * 10)) {
			return (-1);
		}

		// Copy the data from Status into data for return
		for (int i = 0; i < Status[3] - 2; i++) {
			data[i] = Status[5 + i];
		}

#ifdef AX12_READ_DEBUG
		serial_pc::printf("\nStatus Packet\n");
		serial_pc::printf("  Header : 0x%x\n", Status[0]);
		serial_pc::printf("  Header : 0x%x\n", Status[1]);
		serial_pc::printf("  ID : 0x%x\n", Status[2]);
		serial_pc::printf("  Length : 0x%x\n", Status[3]);
		serial_pc::printf("  Error Code : 0x%x\n", Status[4]);

		for (int i = 0; i < Status[3] - 2; i++) {
			serial_pc::printf("  Data : 0x%x\n", Status[5 + i]);
		}

		serial_pc::printf("  Checksum : 0x%x\n", Status[5 + (Status[3] - 2)]);
#endif

	}

	return (Status[4]);
}

template<typename serial>
int AX12<serial>::write(int ID, int start, int bytes, char* data, int flag) {
// 0xff, 0xff, ID, Length, Intruction(write), Address, Param(s), Checksum

	char TxBuf[16];
	char sum = 0;
	char Status[6];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("\nwrite(%d,0x%x,%d,data,%d)\n", ID, start, bytes, flag);
#endif

	// Build the TxPacket first in RAM, then we'll send in one go
#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("\nInstruction Packet\n  Header : 0xFF, 0xFF\n");
#endif

	TxBuf[0] = 0xff;
	TxBuf[1] = 0xff;

	// ID
	TxBuf[2] = ID;
	sum += TxBuf[2];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("  ID : %d\n", TxBuf[2]);
#endif

	// packet Length
	TxBuf[3] = 3 + bytes;
	sum += TxBuf[3];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("  Length : %d\n", TxBuf[3]);
#endif

	// Instruction
	if (flag == 1) {
		TxBuf[4] = 0x04;
		sum += TxBuf[4];
	}
	else {
		TxBuf[4] = 0x03;
		sum += TxBuf[4];
	}

#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("  Instruction : 0x%x\n", TxBuf[4]);
#endif

	// Start Address
	TxBuf[5] = start;
	sum += TxBuf[5];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("  Start : 0x%x\n", TxBuf[5]);
#endif

	// data
	for (uint8_t i = 0; i < bytes; i++) {
		TxBuf[6 + i] = data[i];
		sum += TxBuf[6 + i];

#ifdef AX12_WRITE_DEBUG
		serial_pc::printf("  Data : 0x%x\n", TxBuf[6 + i]);
#endif

	}

	// checksum
	TxBuf[6 + bytes] = 0xFF - sum;

#ifdef AX12_WRITE_DEBUG
	serial_pc::printf("  Checksum : 0x%x\n", TxBuf[6 + bytes]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(TxBuf, 7 + bytes);
		
	serial::lockMutex();
		
	// Wait for data to transmit
	osDelay((7 + bytes) * 1000.0 / _baud);

	// make sure we have a valid return
	Status[4] = 0x00;

			// we'll only get a reply if it was not broadcast
	if (_ID != 0xFE) {

		serial::changeCommunicationMode(serial::communicationMode::RX);

		// response packet is always 6 bytes
		// 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
		// timeout is a little more than the time to transmit
		// the packet back, i.e. 60 bit periods, round up to 100
		int timeout = 0;
		int plen = 0;
		while ((timeout < (60)) && (plen < 6)) {

			if (serial::available()) {
				serial::releaseMutex();
				serial::read_char(Status[plen]);
				serial::lockMutex();
				plen++;
				timeout = 0;
			}
				
			// wait for the bit period
			osDelay(1000.0 / _baud);
			timeout++;
		}
		serial::releaseMutex();
			
		serial::changeCommunicationMode(serial::communicationMode::TX);
		// Build the TxPacket first in RAM, then we'll send in one go
#ifdef AX12_WRITE_DEBUG
		serial_pc::printf("\nStatus Packet\n  Header : 0x%X, 0x%X\n", Status[0], Status[1]);
		serial_pc::printf("  ID : %d\n", Status[2]);
		serial_pc::printf("  Length : %d\n", Status[3]);
		serial_pc::printf("  Error : 0x%x\n", Status[4]);
		serial_pc::printf("  Checksum : 0x%x\n", Status[5]);
#endif


	}

	return (Status[4]); // return error code
}

template class AX12<serial_ax>;