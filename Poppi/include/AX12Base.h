#pragma once

#include <vector>
#include <array>

//#define AX12_TRIGGER_DEBUG
//#define AX12_WRITE_DEBUG
//#define AX12_READ_DEBUG
//#define AX12_DEBUG

class AX12Base
{
public:
	virtual ~AX12Base() {};
	
	enum Mode
	{
		Join, //Positional, default
		Wheel //Continuous rotation
	};
	
	enum Error
	{
		TIMEOUT       = 1 << 7,
		INSTRUCTION   = 1 << 6,
		OVERLOAD      = 1 << 5,
		CHECKSUM      = 1 << 4,
		RANGE         = 1 << 3,
		OVERHEATING   = 1 << 2,
		ANGLE_LIMIT   = 1 << 1,
		INPUT_VOLTAGE = 1,
		NO_ERROR      = 0
	};
	
	static const int ID_BROADCAST = 0xFE;
	
	/** Set the mode of the servo
	* @param mode
	*    0 = Positional, default
	*    1 = Continuous rotation
	* @returns Error Code
	*/
	void SetMode(Mode mode);
	
	/** Set baud rate of all attached servos
	* @param mode
	*    0x01 = 1,000,000 bps
	*    0x03 =   500,000 bps
	*    0x04 =   400,000 bps
	*    0x07 =   250,000 bps
	*    0x09 =   200,000 bps
	*    0x10 =   115,200 bps
	*    0x22 =    57,600 bps
	*    0x67 =    19,200 bps
	*    0xCF =     9,600 bp
	* @returns Error Code
	*/
	Error SetBaudrate(int baud);
	
	/** Set torque either enable or disable
	*/
	Error SetTorque(bool torqueEnable);
	
	/** Set the max torque
	*
	* @param limitTorque 0-1
	* @returns Error Code
	*/
	Error SetTorqueLimit(float limitTorque);
	
	/** Set goal angle in integer degrees, in positional mode
	*
	* @param degrees 0-300
	* @returns Error Code
	*/
	Error SetGoalPosition(int degrees);
	
	/** Set the speed of the servo
	*
	* If the mode is Joint
	* @param speed 0-1.0
	*    If it is set to 0, it means the maximum rpm of the motor is used without controlling the speed.
	*    If it is 1.0, it is about 114rpm.
	* If the mode is Wheel
	* @param speed, -1.0 to 1.0
	*   -1.0 = full speed clock wise
	*    1.0 = full speed counter clock wise
	* @returns Error Code
	*/
	Error SetSpeed(float speed);
	
	/** Set the clockwise limit of the servo
	*
	* @param degrees, 0-300
	* @returns Error Code
	*/
	Error SetClockwiseLimit(int degrees);
	
	/** Set the counter-clockwise limit of the servo
	*
	* @param degrees, 0-300
	* @returns Error Code
	*/
	Error SetCounterClockwiseLimit(int degrees);
	
	/** Change the ID of a servo
	*
	* @param CurentID 1-255
	* @param NewID 1-255
	* @returns Error Code
	*
	* If a servo ID is not know, the broadcast address of 0 can be used for CurrentID.
	* In this situation, only one servo should be connected to the bus
	*/
	Error SetID(int currentID, int newID);
	
	/** Set the state of the led
	* @param ledOn true or false
	* @returns Error Code
	*/
	Error SetLED(bool ledOn);
	
	/** Set minimum and maximum angle of the servo
	*
	* @param minAngle, 0-300
	* @param maxAngle, 0-300
	* @returns Error Code
	*/
	int SetExtremum(int minAngle, int maxAngle);
	
	/** Poll to see if the servo is moving
	*
	* @returns true is the servo is moving
	*/
	Error IsMoving(bool& isMoving);
	
	/** Poll to see if the torque is enable
	*/
	Error IsTorqueEnable(bool& isTorqueEnable);
	
	/** Read the goal angle of the servo
	*
	* @param float in the range 0.0-300.0
	* @returns Error Code
	*/
	Error GetGoalPosition(float& angle);
	
	/** Read the current angle of the servo
	*
	* @param float in the range 0.0-300.0
	* @returns Error Code
	*/
	Error GetPresentPosition(float& angle);
	
	/** Read the current load of the servo
	*
	* @param float load
	*   -1.0 = full load clock wise
	*    1.0 = full load counter clock wise
	* @returns Error Code
	*/
	Error GetPresentLoad(float& load);
	
	/** Read the current speed of the servo
	*
	* @param float velocity
	*   -1.0 = full speed clock wise
	*    1.0 = full speed counter clock wise
	* @returns Error Code
	*/
	Error GetPresentSpeed(float& speed);
	
	/** Reat the limit torque
	*
	* @param float limit torque
	* @returns Error Code
	*/
	Error GetTorqueLimit(float& torqueLimit);
	
	/** Read the temperature of the servo
	*
	* @param float temperature
	* @returns Error Code
	*/
	Error GetTemperature(float& temp);
	
	/** Read the supply voltage of the servo
	*
	* @param float voltage
	* @returns Error Code
	*/
	Error GetVolts(float& volts);
	
	/**  Read the state of the led
	*
	* @param bool isLedOn
	* @returns Error Code
	*/
	Error GetLED(bool& led);
	
	Error Ping();
	
protected:
	int _ID;
	int _baud;
	Mode _mode;
	bool _shouldWaitForTrigger;
	
	std::vector<char> _txBuf;
	std::vector<char> _rxBuf;
	std::vector<char> _data;
	
	/*
//EEPROM
LIMIT_TEMPERATURE, // 0x0B
DOWN_LIMIT_VOLTAGE, // 0x0C
UP_LIMIT_VOLTAGE, // 0x0D
MAX_TORQUE_L, // 0x0E
MAX_TORQUE_H, // 0x0F
STATUS_RETURN_LEVEL, // 0x10

//RAM
CW_COMPLIANCE_MARGIN, // 0x1A
CCW_COMPLIANCE_MARGIN, // 0x1B
CW_COMPLIANCE_SLOPE, // 0x1C
CCW_COMPLIANCE_SLOPE, // 0x1D
TORQUE_LIMIT_L, // 0x22
TORQUE_LIMIT_H, // 0x23
REGISTERED_INSTRUCTION, // 0x2C
LOCK, // 0x2F
PUNCH_L, // 0x30
PUNCH_H // 0x31 */
	
	struct Register
	{
		const uint8_t address;
		const uint8_t length;
	};
	
	//EEPROM Kept after reboot
	static constexpr Register REG_ID = { 0x3, 1 };
	static constexpr Register REG_BAUD = { 0x4, 1 };
	static constexpr Register REG_CLOCKWISE_LIMIT = { 0x06, 2 };
	static constexpr Register REG_COUNTERCLOCKWISE_LIMIT = { 0x08, 2 };
	
	//RAM Reset after reboot
	static constexpr Register REG_TORQUE_ENABLE = { 0x18, 1 };
	static constexpr Register REG_LED = { 0x19, 1 };
	static constexpr Register REG_GOAL_POSITION = { 0x1E, 2 };
	static constexpr Register REG_MOVING_SPEED = { 0X20, 2 };
	static constexpr Register REG_TORQUE_LIMIT = { 0x22, 2 };
	static constexpr Register REG_PRESENT_POSITION = { 0x24, 2 };
	static constexpr Register REG_PRESENT_SPEED = { 0x26, 2 };
	static constexpr Register REG_PRESENT_VOLTAGE = { 0x2A, 1 };
	static constexpr Register REG_PRESENT_LOAD = { 0x28, 2 };
	static constexpr Register REG_PRESENT_TEMPERATURE = { 0x2B, 1 };
	static constexpr Register REG_MOVING = { 0x2E, 1 };
	
	enum Instruction
	{
		PING       = 0x01, // No execution. It is used when controller is ready to receive Status Packet
		READ_DATA  = 0x02, // This command reads data from Dynamixel
		WRITE_DATA = 0x03, // This command writes data to Dynamixel
		REG_WRITE  = 0x04, // It is similar to WRITE_DATA, but it remains in the standby state without being executed until the ACTION command arrives.
		ACTION     = 0x05, // This command initiates motions registered with REG_WRITE
		RESET      = 0x06, // This command restores the state of Dynamixel to the factory default setting.
		SYNC_WRITE = 0x83 // This command is used to control several Dynamixels simultaneously at a time.
	};
	
protected:
	Error read(int ID, const Register& reg);
	Error write(int ID, const Register& reg, bool shouldWaitForTrigger);
	
	virtual Error read() = 0;
	virtual Error write() = 0;
};