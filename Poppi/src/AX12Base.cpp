#include "AX12Base.h"
#include <cmath>

//EEPROM Kept after reboot
constexpr AX12Base::Register AX12Base::REG_ID = AX12Base::Register(0x3, 1);
constexpr AX12Base::Register AX12Base::REG_BAUD = AX12Base::Register(0x4, 1);
constexpr AX12Base::Register AX12Base::REG_CLOCKWISE_LIMIT = AX12Base::Register(0x06, 2);
constexpr AX12Base::Register AX12Base::REG_COUNTERCLOCKWISE_LIMIT = AX12Base::Register(0x08, 2);
	
//RAM Reset after reboot
constexpr AX12Base::Register AX12Base::REG_TORQUE_ENABLE = AX12Base::Register(0x18, 1);
constexpr AX12Base::Register AX12Base::REG_LED = AX12Base::Register(0x19, 1);
constexpr AX12Base::Register AX12Base::REG_GOAL_POSITION = AX12Base::Register(0x1E, 2);
constexpr AX12Base::Register AX12Base::REG_MOVING_SPEED = AX12Base::Register(0X20, 2);
constexpr AX12Base::Register AX12Base::REG_TORQUE_LIMIT = AX12Base::Register(0x22, 2);
constexpr AX12Base::Register AX12Base::REG_PRESENT_POSITION = AX12Base::Register(0x24, 2);
constexpr AX12Base::Register AX12Base::REG_PRESENT_SPEED = AX12Base::Register(0x26, 2);
constexpr AX12Base::Register AX12Base::REG_PRESENT_LOAD = AX12Base::Register(0x28, 2);
constexpr AX12Base::Register AX12Base::REG_PRESENT_VOLTAGE = AX12Base::Register(0x2A, 1);
constexpr AX12Base::Register AX12Base::REG_PRESENT_TEMPERATURE = AX12Base::Register(0x2B, 1);
constexpr AX12Base::Register AX12Base::REG_MOVING = AX12Base::Register(0x2E, 1);

void AX12Base::SetMode(Mode mode) {

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


Error  AX12Base::SetBaudrate(int baud) {

	std::array<unsigned char, REG_BAUD.length> data;
	data[0] = _baud;

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting Baud rate to %d", baud);
#endif

	Error ErrorCode = write(ID_BROADCAST, REG_BAUD, data, 0);

	_baud = baud;
	
	return ErrorCode;
}

Error  AX12Base::SetTorque(bool torqueEnable) {

	std::array<unsigned char, REG_TORQUE_ENABLE.length> data;
	data[0] = torqueEnable;

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting Torque to %d", torqueEnable);
#endif

	return write(_ID, REG_TORQUE_ENABLE, data, _shouldWaitForTrigger);
}

Error AX12Base::SetTorqueLimit(float limitTorque) {
	
	std::array<unsigned char, REG_TORQUE_LIMIT.length> data;
	int torque = (0x3ff * std::abs(limitTorque));

	data[0] = torque & 0xff;  // bottom 8 bits
	data[1] = torque >> 8;    // top 8 bits

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting Torque limit to %f", limitTorque);
#endif

	return write(_ID, REG_TORQUE_LIMIT, data, _shouldWaitForTrigger);
}


Error AX12Base::SetGoalPosition(int degrees) {

	std::array<unsigned char, REG_GOAL_POSITION.length> data;

	// 1023 / 300 * degrees
	short goal = (1023 * degrees) / 300;
#ifdef AX12_DEBUG
	serial_pc::printfln("SetGoal to %d", goal);
#endif

	data[0] = goal & 0xff;  // bottom 8 bits
	data[1] = goal >> 8;    // top 8 bits

	// write the packet, return the error code
	return write(_ID, REG_GOAL_POSITION, data, _shouldWaitForTrigger);
}

Error AX12Base::SetSpeed(float speed) {

	// bit 10     = direction, 0 = CCW, 1=CW //If in Wheel mode
	// bits 9-0   = Speed
	std::array<unsigned char, REG_MOVING_SPEED.length> data;

	int goal = (0x3ff * std::abs(speed));

	// Set direction CW if we have a negative speed
if((_mode == Mode::Wheel) && (speed < 0))
	goal |= (0x1 << 10);

	data[0] = goal & 0xff;  // bottom 8 bits
	data[1] = goal >> 8;    // top 8 bits

	// write the packet, return the error code
	return write(_ID, REG_MOVING_SPEED, data, _shouldWaitForTrigger);
}


Error AX12Base::SetClockwiseLimit(int degrees) {

	degrees = std::max(degrees, 0);
	degrees = std::min(degrees, 300);
		
	std::array<unsigned char, REG_CLOCKWISE_LIMIT.length> data;

	// 1023 / 300 * degrees
	short limit = (1023 * degrees) / 300;

#ifdef AX12_DEBUG
	serial_pc::printfln("SetClockwiseLimit to 0x%x", limit);
#endif

	data[0] = limit & 0xff;  // bottom 8 bits
	data[1] = limit >> 8;    // top 8 bits

	// write the packet, return the error code
	return write(_ID, REG_CLOCKWISE_LIMIT, data, _shouldWaitForTrigger);
}

Error AX12Base::SetCounterClockwiseLimit(int degrees) {

	degrees = std::max(degrees, 0);
	degrees = std::min(degrees, 300);
		
	std::array<unsigned char, REG_COUNTERCLOCKWISE_LIMIT.length> data;

	// 1023 / 300 * degrees
	short limit = (1023 * degrees) / 300;

#ifdef AX12_DEBUG
	serial_pc::printfln("SetCounterClockwiseLimit to 0x%x", limit);
#endif

	data[0] = limit & 0xff;  // bottom 8 bits
	data[1] = limit >> 8;    // top 8 bits

	// write the packet, return the error code
	return write(_ID, REG_COUNTERCLOCKWISE_LIMIT, data, _shouldWaitForTrigger);
}

Error AX12Base::SetID(int currentID, int newID) {

	std::array<unsigned char, REG_ID.length> data;
	data[0] = newID;

#ifdef AX12_DEBUG
	serial_pc::printfln("Setting ID from 0x%x to 0x%x", currentID, newID);
#endif
	_ID = newID;
	
	return write(currentID, REG_ID, data, _shouldWaitForTrigger);
}

Error AX12Base::SetLED(bool ledOn) {
	
	std::array<unsigned char, REG_LED.length> data;
	data[0] = ledOn;

#ifdef AX12_DEBUG
	serial_pc::printfln("SetLED to 0x%x", ledOn);
#endif
	
	return write(_ID, REG_LED, data, _shouldWaitForTrigger);
}

int AX12Base::SetExtremum(int minAngle, int maxAngle) {
	
#ifdef AX12_DEBUG
	serial_pc::printfln("SetExtremum(%d)", _ID);
#endif
	
	int ErrorCode = SetClockwiseLimit(minAngle);
	ErrorCode |= SetCounterClockwiseLimit(maxAngle);
	return ErrorCode;
}

Error AX12Base::IsMoving(bool& isMoving) {
	
#ifdef AX12_DEBUG
	serial_pc::printfln("isMoving(%d)", _ID);
#endif
	
	unsigned char data[REG_MOVING.length];
	
	Error ErrorCode = read(_ID, REG_MOVING, data);
	
	isMoving = (data[0] == 1);
	
	return ErrorCode;
}

Error AX12Base::IsTorqueEnable(bool& isTorqueEnable) {
	
#ifdef AX12_DEBUG
	serial_pc::printfln("isTorqueEnable(%d)", _ID);
#endif
	
	unsigned char data[REG_TORQUE_ENABLE.length];
	
	Error ErrorCode = read(_ID, REG_TORQUE_ENABLE, data);
	
	isTorqueEnable = (data[0] == 1);
	
	return ErrorCode;
}

Error AX12Base::GetGoalPosition(float& angle) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetGoalPosition(%d)", _ID);
#endif

	unsigned char data[REG_GOAL_POSITION.length];

	Error ErrorCode = read(_ID, REG_GOAL_POSITION, data);
	
	int position = data[0] + (data[1] << 8);
	angle = (position * 300) / 1024;

	return ErrorCode;
}

Error AX12Base::GetPresentPosition(float& angle) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetPresentPosition(%d)", _ID);
#endif

	unsigned char data[REG_PRESENT_POSITION.length];

	Error ErrorCode = read(_ID, REG_PRESENT_POSITION, data);
	
	int position = data[0] + (data[1] << 8);
	angle = (position * 300) / 1024;
	
	return ErrorCode;
}

Error AX12Base::GetPresentLoad(float& load) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetPresentLoad(%d)", _ID);
#endif

	unsigned char data[REG_PRESENT_LOAD.length];

	Error ErrorCode = read(_ID, REG_PRESENT_LOAD, data);

	load = data[0] + ((0x03 & data[1]) << 8);
	load /= 1023;
	if (data[1] & 0x07)
		load *= -1;
	
	return ErrorCode;
}

Error AX12Base::GetPresentSpeed(float& speed) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetPresentSpeed(%d)", _ID);
#endif
	
	unsigned char data[REG_PRESENT_SPEED.length];

	Error ErrorCode = read(_ID, REG_PRESENT_SPEED, data);

	speed = data[0] + ((0x03 & data[1]) << 8);
	speed /= 1023;
	if (data[1] & 0x07)
		speed *= -1;
	
	return ErrorCode;
}

Error AX12Base::GetTorqueLimit(float& torqueLimit) {
	
#ifdef AX12_DEBUG
	serial_pc::printfln("GetTorqueLimit(%d)", _ID);
#endif

	unsigned char data[REG_TORQUE_LIMIT.length];

	Error ErrorCode = read(_ID, REG_TORQUE_LIMIT, data);

	torqueLimit = data[0] + ((0x03 & data[1]) << 8);
	torqueLimit /= 1023;
	
	return ErrorCode;
}


Error AX12Base::GetTemperature(float& temp) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetTemp(%d)", _ID);
#endif

	unsigned char data[REG_PRESENT_TEMPERATURE.length];
	
	Error ErrorCode = read(_ID, REG_PRESENT_TEMPERATURE, data);
	temp = data[0];
	
	return ErrorCode;
}

Error AX12Base::GetVolts(float& volts) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetVolts(%d)", _ID);
#endif

	unsigned char data[REG_PRESENT_VOLTAGE.length];
	
	Error ErrorCode = read(_ID, REG_PRESENT_VOLTAGE, data);
	
	volts = data[0] / 10.0;
	
	return ErrorCode;
}

Error AX12Base::GetLED(bool& led) {

#ifdef AX12_DEBUG
	serial_pc::printfln("GetVolts(%d)", _ID);
#endif

	unsigned char data[REG_LED.length];
	
	Error ErrorCode = read(_ID, REG_LED, data);
	
	led = data[0] == 1;
	
	return ErrorCode;
}

Error AX12Base::read(int ID, const Register& reg, unsigned char*data)
{
	_txBuf.clear();
	char sum = 0;
	_rxBuf.resize(6 + reg.length);

	_rxBuf[4] = 0xFE;  // return code

#ifdef AX12_READ_DEBUG
		serial_pc::printfln("read(%d,0x%x,%d,data)", ID, start, bytes);
#endif

	// Build the TxPacket first in RAM, then we'll send in one go
#ifdef AX12_READ_DEBUG
		serial_pc::printfln("Instruction Packet");
	serial_pc::printfln("Header : 0xFF, 0xFF");
#endif

	_txBuf.push_back(0xff);
	_txBuf.push_back(0xff);

	// ID
	_txBuf.push_back(ID);
	sum += _txBuf.back();

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  ID : %d", TxBuf[2]);
#endif

	// Packet Length
	_txBuf.push_back(0x4);     // Length = 4 : (0xFF, 0xFF, id, length)
	sum += _txBuf.back();

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Length : 0x%x", TxBuf[3]);
#endif

	// Instruction - Read
	_txBuf.push_back(Instruction::READ_DATA);
	sum += _txBuf.back();

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Instruction : 0x%x", TxBuf[4]);
#endif

	// Start Address
	_txBuf.push_back(reg.address);
	sum += _txBuf.back();

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Start Address : 0x%x", TxBuf[5]);
#endif

	// Bytes to read
	_txBuf.push_back(reg.length);
	sum += _txBuf.back();

#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  No bytes : 0x%x", TxBuf[6]);
#endif

	// Checksum
	_txBuf.push_back(~sum);
#ifdef AX12_READ_DEBUG
	serial_pc::printfln("  Checksum : 0x%x", TxBuf[7]);
#endif

	return read(data);
}

template <std::size_t size>
Error AX12Base::write(int ID, const Register& reg, const std::array<unsigned char, size> &data, bool shouldWaitForTrigger)
{
	// 0xff, 0xff, ID, Length, Intruction(write), Address, Param(s), Checksum

	_txBuf.clear();
	
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

	_txBuf.push_back(0xff);
	_txBuf.push_back(0xff);

	// ID
	_txBuf.push_back(ID);
	sum += _txBuf.back();

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  ID : %d", TxBuf[2]);
#endif

	// packet Length
	_txBuf.push_back(3 + reg.length);
	sum += _txBuf.back();

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Length : %d", TxBuf[3]);
#endif

	// Instruction
	_txBuf.push_back(shouldWaitForTrigger ? Instruction::REG_WRITE : Instruction::WRITE_DATA);
	sum += _txBuf.back();

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Instruction : 0x%x", TxBuf[4]);
#endif

	// Start Address
	_txBuf.push_back(reg.address);
	sum += _txBuf.back();

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Start : 0x%x", TxBuf[5]);
#endif

	// data
	for(uint8_t i = 0 ; i < reg.length ; i++) {
		_txBuf.push_back(data[i]);
		sum += _txBuf.back();

#ifdef AX12_WRITE_DEBUG
		serial_pc::printfln("  Data : 0x%x", TxBuf[6 + i]);
#endif

	}

	// checksum
	_txBuf.push_back(~sum);

#ifdef AX12_WRITE_DEBUG
	serial_pc::printfln("  Checksum : 0x%x", TxBuf[6 + bytes]);
#endif

	return write();
}