#include "AX12.h"
#include "cmsis_os.h"
#include <algorithm>
#include <cmath>
#include "Useful.h"
#include <vector>
#include <array>

template<typename serial>
AX12<serial>::~AX12()
{
}


template<typename serial>
AX12<serial>::AX12(int ID, int baud, Mode mode, bool shouldWaitForTrigger)
{
	_ID = ID;
	_baud = baud;
	_mode = mode;
	_shouldWaitForTrigger = shouldWaitForTrigger;
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

	char data[1];
	data[0] = _baud;

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting Baud rate to %d", baud);
#endif

	int rVal = write(0xFE, REG_BAUD, data, 0);

	_baud = baud;
	
	return rVal;
}

template<typename serial>
int  AX12<serial>::SetTorque(bool torqueEnable) {

	char data[1];
	data[0] = torqueEnable;

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting Torque to %d", baud);
#endif

	return write(_ID, REG_TORQUE_ENABLE, data, _shouldWaitForTrigger);
}

template<typename serial>
int AX12<serial>::SetGoalPosition(int degrees) {

	char data[2];

	// 1023 / 300 * degrees
	short goal = (1023 * degrees) / 300;
#ifdef AX12_DEBUG
	serial_pc::printfln("SetGoal to 0x%x", goal);
#endif

	data[0] = goal & 0xff; // bottom 8 bits
	data[1] = goal >> 8;   // top 8 bits

	// write the packet, return the error code
	int rVal = write(_ID, REG_GOAL_POSITION, data, _shouldWaitForTrigger);
#ifdef UNITY
	serial_pc::printfln("AX12 move %d %d", _ID, degrees);
#endif
	
	return rVal;
}


template<typename serial>
int AX12<serial>::SetSpeed(float speed) {

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
	int rVal = write(_ID, REG_MOVING_SPEED, data, _shouldWaitForTrigger);

	return rVal;
}


template<typename serial>
int AX12<serial>::SetClockwiseLimit(int degrees) {

	degrees = std::max(degrees, 0);
	degrees = std::min(degrees, 300);
		
	char data[2];

	// 1023 / 300 * degrees
	short limit = (1023 * degrees) / 300;

#ifdef AX12_DEBUG
	serial_pc::printfln("SetClockwiseLimit to 0x%x", limit);
#endif

	data[0] = limit & 0xff; // bottom 8 bits
	data[1] = limit >> 8;   // top 8 bits

	// write the packet, return the error code
	return write(_ID, REG_Clockwise_LIMIT, data, _shouldWaitForTrigger);
}

template<typename serial>
int AX12<serial>::SetCounterClockwiseLimit(int degrees) {

	degrees = std::max(degrees, 0);
	degrees = std::min(degrees, 300);
		
	char data[2];

	// 1023 / 300 * degrees
	short limit = (1023 * degrees) / 300;

#ifdef AX12_DEBUG
	serial_pc::printfln("SetCounterClockwiseLimit to 0x%x", limit);
#endif

	data[0] = limit & 0xff; // bottom 8 bits
	data[1] = limit >> 8;   // top 8 bits

	// write the packet, return the error code
	return write(_ID, REG_CounterClockwise_LIMIT, data, _shouldWaitForTrigger);
}

template<typename serial>
int AX12<serial>::SetID(int currentID, int newID) {

	char data[1];
	data[0] = newID;

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting ID from 0x%x to 0x%x", currentID, newID);
#endif
	_ID = newID;
	//TODO: catch error
	return write(currentID, REG_ID, data, _shouldWaitForTrigger);

}

template<typename serial>
int AX12<serial>::SetLED(bool ledOn) {
	char data[1];
	data[0] = ledOn;

#ifdef AX12_DEBUG
	serial_pc::printfln("SetLED to 0x%x", ledOn);
#endif
	
	return write(_ID, REG_LED, data, _shouldWaitForTrigger);
}

template<typename serial>
bool AX12<serial>::isMoving() {
	char data[1];
	read(_ID, REG_MOVING, data);
	return (data[0] == 1);
}

template<typename serial>
bool AX12<serial>::isTorqueEnable() {
	char data[1];
	read(_ID, REG_TORQUE_ENABLE, data);
	return (data[0] == 1);
}

template<typename serial>
float AX12<serial>::GetGoalPosition() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetGoalPosition(%d)", _ID);
#endif

	char data[2];

	int ErrorCode = read(_ID, REG_GOAL_POSITION, data);
	int position = data[0] + (data[1] << 8);
	float angle = (position * 300) / 1024;

	return angle;
}

template<typename serial>
float AX12<serial>::GetPresentPosition() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetPresentPosition(%d)", _ID);
#endif

	char data[2];

	int ErrorCode = read(_ID, REG_PRESENT_POSITION, data);
	int position = data[0] + (data[1] << 8);
	float angle = (position * 300) / 1024;

	return angle;
}
	
template<typename serial>
float AX12<serial>::GetPresentSpeed() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetPresentSpeed(%d)", _ID);
#endif

	char data[2];

	int ErrorCode = read(_ID, REG_PRESENT_SPEED, data);

	float speed = data[0] + (0x03 & data[1] << 8);
	speed /= 1023;
	if (data[1] & 0x07)
		speed *= -1;
	
	return speed;
}

template<typename serial>
float AX12<serial>::GetPresentLoad() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetPresentLoad(%d)", _ID);
#endif

	char data[2];

	int ErrorCode = read(_ID, REG_PRESENT_LOAD, data);

	float load = data[0] + (0x03 & data[1] << 8);
	load /= 1023;
	if (data[1] & 0x07)
		load *= -1;
	
	return load;
}

template<typename serial>
float AX12<serial>::GetTemp() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetTemp(%d)", _ID);
#endif

	char data[1];
	int ErrorCode = read(_ID, REG_PRESENT_TEMPERATURE, data);
	float temp = data[0];
	return temp;
}

template<typename serial>
float AX12<serial>::GetVolts() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetVolts(%d)", _ID);
#endif

	char data[1];
	
	int ErrorCode = read(_ID, REG_PRESENT_VOLTAGE, data);
	float volts = data[0] / 10.0;
	return volts;
}

template<typename serial>
bool AX12<serial>::GetLED() {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetVolts(%d)", _ID);
#endif

	char data[1];
	
	int ErrorCode = read(_ID, REG_LED, data);
	bool volts = data[0] == 1;
	return volts;
}

template<typename serial>
int AX12<serial>::read(int ID, Register reg, char* data) {

	_txBuf.resize(8);
	char sum = 0;
	_rxBuf.resize(6 + reg.length);

	_rxBuf[4] = 0xFE; // return code

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("read(%d,0x%x,%d,data)", ID, start, bytes);
#endif

	// Build the TxPacket first in RAM, then we'll send in one go
#ifdef AX12_READ_DEBUG
	serial_pc::printfln("Instruction Packet");
	serial_pc::printfln("Header : 0xFF, 0xFF");
#endif

	_txBuf[0] = 0xff;
	_txBuf[1] = 0xff;

	// ID
	_txBuf[2] = ID;
	sum += _txBuf[2];

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  ID : %d", TxBuf[2]);
#endif

	// Packet Length
	_txBuf[3] = 0x4;    // Length = 4 : (0xFF, 0xFF, id, length)
	sum += _txBuf[3];            // Accumulate the packet sum

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Length : 0x%x", TxBuf[3]);
#endif

	// Instruction - Read
	_txBuf[4] = Instruction::READ_DATA;
	sum += _txBuf[4];

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Instruction : 0x%x", TxBuf[4]);
#endif

	// Start Address
	_txBuf[5] = reg.address;
	sum += _txBuf[5];

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Start Address : 0x%x", TxBuf[5]);
#endif

	// Bytes to read
	_txBuf[6] = reg.length;
	sum += _txBuf[6];

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  No bytes : 0x%x", TxBuf[6]);
#endif

	// Checksum
	_txBuf[7] = 0xFF - sum;
#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Checksum : 0x%x", TxBuf[7]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(_txBuf);
		
	serial::lockMutex();
		
	// Wait for the bytes to be transmitted
	osDelay(_txBuf.size() * 1000.0 / _baud);

	// Skip if the read was to the broadcast address
	if (ID != 0xFE) {

		serial::changeCommunicationMode(serial::communicationMode::RX);


		// response packet is always 6 + bytes
		// 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
		// timeout is a little more than the time to transmit
		// the packet back, i.e. (6+bytes)*10 bit periods

		int timeout = 0;
		int plen = 0;
		while ((timeout < (_rxBuf.size() * 10)) && (plen < _rxBuf.size())) {

			if (serial::available()) {
				serial::releaseMutex();
				serial::read_char(_rxBuf[plen]);
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

		if (timeout == (_rxBuf.size() * 10)) {
			return (-1);
		}

		// Copy the data from Status into data for return
		for (int i = 0; i < _rxBuf[3] - 2; i++) {
			data[i] = _rxBuf[5 + i];
		}

#ifdef AX12_READ_DEBUG
		serial_pc::printfln("");
		serial_pc::printfln("Status Packet");
		serial_pc::printfln("  Header : 0x%x", _rxBuf[0]);
		serial_pc::printfln("  Header : 0x%x", _rxBuf[1]);
		serial_pc::printfln("  ID : 0x%x", _rxBuf[2]);
		serial_pc::printfln("  Length : 0x%x", _rxBuf[3]);
		serial_pc::printfln("  Error Code : 0x%x", _rxBuf[4]);

		for (int i = 0; i < _rxBuf[3] - 2; i++) {
			serial_pc::printfln("  Data : 0x%x", _rxBuf[5 + i]);
		}

		serial_pc::printfln("  Checksum : 0x%x", _rxBuf[5 + (_rxBuf[3] - 2)]);
#endif

	}

	return (_rxBuf[4]);
}

template<typename serial>
int AX12<serial>::write(int ID, Register reg, char* data, bool shouldWaitForTrigger) {
// 0xff, 0xff, ID, Length, Intruction(write), Address, Param(s), Checksum

	_txBuf.resize(7 + reg.length);
	char sum = 0;
	_rxBuf.resize(6);
	
#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("write(%d,0x%x,%d,data,%d)", ID, start, bytes, _shouldWaitForTrigger);
#endif

	// Build the TxPacket first in RAM, then we'll send in one go
#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("Instruction Packet");
	serial_pc::printfln("  Header : 0xFF, 0xFF");
#endif

	_txBuf[0] = 0xff;
	_txBuf[1] = 0xff;

	// ID
	_txBuf[2] = ID;
	sum += _txBuf[2];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  ID : %d", TxBuf[2]);
#endif

	// packet Length
	_txBuf[3] = 3 + reg.length;
	sum += _txBuf[3];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Length : %d", TxBuf[3]);
#endif

	// Instruction
	_txBuf[4] = shouldWaitForTrigger ? Instruction::REG_WRITE : Instruction::WRITE_DATA;
	sum += _txBuf[4];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Instruction : 0x%x", TxBuf[4]);
#endif

	// Start Address
	_txBuf[5] = reg.address;
	sum += _txBuf[5];

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Start : 0x%x", TxBuf[5]);
#endif

	// data
	for (uint8_t i = 0; i < reg.length; i++) {
		_txBuf[6 + i] = data[i];
		sum += _txBuf[6 + i];

#ifdef AX12_WRITE_DEBUG
		serial_pc::printfln("  Data : 0x%x", TxBuf[6 + i]);
#endif

	}

	// checksum
	_txBuf[6 + reg.length] = 0xFF - sum;

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Checksum : 0x%x", TxBuf[6 + bytes]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(_txBuf);
		
	serial::lockMutex();
		
	// Wait for data to transmit
	osDelay(_txBuf.size() * 1000.0 / _baud);

	// make sure we have a valid return
	_rxBuf[4] = 0x00;

			// we'll only get a reply if it was not broadcast
	if (ID != 0xFE) {
		
		_rxBuf[4] = 0xFE; // return code

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
				serial::read_char(_rxBuf[plen]);
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
		serial_pc::printfln("");
		serial_pc::printfln("Status Packet");
		serial_pc::printfln("  Header : 0x%X, 0x%X", _rxBuf[0], _rxBuf[1]);
		serial_pc::printfln("  ID : %d", _rxBuf[2]);
		serial_pc::printfln("  Length : %d", _rxBuf[3]);
		serial_pc::printfln("  Error : 0x%x", _rxBuf[4]);
		serial_pc::printfln("  Checksum : 0x%x", _rxBuf[5]);
#endif


	}

	return _rxBuf[4]; // return error code
}

template<typename serial>
void AX12<serial>::trigger() {

	_txBuf.resize(6);
	char sum = 0;

#ifdef AX12_TRIGGER_DEBUG
	// Build the TxPacket first in RAM, then we'll send in one go
	serial_pc::printfln("Triggered");
	serial_pc::printfln("Trigger Packet");
	serial_pc::printfln("  Header : 0xFF, 0xFF");
#endif

	_txBuf[0] = 0xFF;
	_txBuf[1] = 0xFF;

	// ID - Broadcast
	_txBuf[2] = 0xFE;
	sum += _txBuf[2];

#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  ID : %d", _rxBuf[2]);
#endif

	// Length
	_txBuf[3] = 0x02;
	sum += _txBuf[3];

#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  Length %d", _rxBuf[3]);
#endif

	// Instruction - ACTION
	_txBuf[4] = Instruction::ACTION;
	sum += _txBuf[4];

#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  Instruction 0x%X", _rxBuf[4]);
#endif

	// Checksum
	_txBuf[5] = 0xFF - sum;
#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  Checksum 0x%X", _rxBuf[5]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(_txBuf);
		
	// This is a broadcast packet, so there will be no reply
	return;
}

template class AX12<serial_ax>;