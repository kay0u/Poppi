#pragma once

//#define UNITY
//#define AX12_TRIGGER_DEBUG
//#define AX12_WRITE_DEBUG
//#define AX12_READ_DEBUG
//#define AX12_DEBUG

template<typename serial>
class AX12
{
public:
	enum Mode
	{
		Join, //Positional, default
		Wheel //Continuous rotation
	};
	AX12() = delete;
	
	~AX12();
	
	/** Create an AX12 servo object connected to the specified serial port, with the specified ID
	*
	* @param int ID, the Bus ID of the servo 1-255
	*/
	AX12(int ID, int baud = 1000000, Mode mode = Mode::Join, bool shouldWaitForTrigger = false);
	
	/** Set the mode of the servo
	* @param mode
	*    0 = Positional, default
	*    1 = Continuous rotation
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
	*/
	int SetBaudrate(int baud);
	
	/** Set torque either enable or disable
	*/
	int SetTorque(bool torqueEnable);
	
	/** Set goal angle in integer degrees, in positional mode
	*
	* @param degrees 0-300
	*/
	int SetGoalPosition(int degrees);
	
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
	*/
	int SetSpeed(float speed);
	
	/** Set the clockwise limit of the servo
	*
	* @param degrees, 0-300
	*/
	int SetClockwiseLimit(int degrees);
	
	/** Set the counter-clockwise limit of the servo
	*
	* @param degrees, 0-300
	*/
	int SetCounterClockwiseLimit(int degrees);
	
	/** Change the ID of a servo
	*
	* @param CurentID 1-255
	* @param NewID 1-255
	*
	* If a servo ID is not know, the broadcast address of 0 can be used for CurrentID.
	* In this situation, only one servo should be connected to the bus
	*/
	int SetID(int currentID, int newID);
	
	/** Set the state of the led
	* @param ledOn true or false
	*/
	int SetLED(bool ledOn);
	
	/** Poll to see if the servo is moving
	*
	* @returns true is the servo is moving
	*/
	bool isMoving();
	
	/** Poll to see if the torque is enable
	*/
	bool isTorqueEnable();
	
	/*Send the broadcast "trigger" command, to activate any outstanding registered commands
	*/
	void trigger();
	
	/** Read the goal angle of the servo
	*
	* @returns float in the range 0.0-300.0
	*/
	float GetGoalPosition();
	
	/** Read the current angle of the servo
	*
	* @returns float in the range 0.0-300.0
	*/
	float GetPresentPosition();
	
	/** Read the current load of the servo
	*
	* @returns float load
	*   -1.0 = full load clock wise
	*    1.0 = full load counter clock wise
	*/
	float GetPresentLoad();
	
	/** Read the current speed of the servo
	*
	* @returns float velocity
	*   -1.0 = full speed clock wise
	*    1.0 = full speed counter clock wise
	*/
	float GetPresentSpeed();
	
	/** Read the temperature of the servo
	*
	* @returns float temperature
	*/
	float GetTemp();
	
	/** Read the supply voltage of the servo
	*
	* @returns float voltage
	*/
	float GetVolts();
	
	/**  Read the state of the led
	*
	* @returns bool isLedOn
	*/
	bool GetLED();
	
private:
	int _ID;
	int _baud;
	Mode _mode;
	bool _shouldWaitForTrigger;
	
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
		Register(unsigned addr, unsigned len)
			: address(addr)
			, length(len)
		{
			address = addr;
			length = len;
		}
		unsigned address;
		unsigned length;
	};
	
	//EEPROM Kept after reboot
	const Register REG_ID = Register(0x3, 1);
	const Register REG_BAUD = Register(0x4, 1);
	const Register REG_Clockwise_LIMIT = Register(0x06, 2);
	const Register REG_CounterClockwise_LIMIT = Register(0x08, 2);
	
	//RAM Reset after reboot
	const Register REG_TORQUE_ENABLE = Register(0x18, 1);
	const Register REG_LED = Register(0x19, 1);
	const Register REG_GOAL_POSITION = Register(0x1E, 2);
	const Register REG_MOVING_SPEED = Register(0X20, 2);
	//TORQUE_LIMIT
	const Register REG_PRESENT_POSITION = Register(0x24, 2);
	const Register REG_PRESENT_SPEED = Register(0x26, 2);
	const Register REG_PRESENT_LOAD = Register(0x28, 2);
	const Register REG_PRESENT_VOLTAGE = Register(0x2A, 1);
	const Register REG_PRESENT_TEMPERATURE = Register(0x2B, 1);
	const Register REG_MOVING = Register(0x2E, 1);
	
	
private:
	int read(int ID, Register reg, char* data);
	int write(int ID, Register reg, char* data, bool shouldWaitForTrigger);
};

