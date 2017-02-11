#pragma once

//#define UNITY
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
	
	~AX12();
	
	/** Create an AX12 servo object connected to the specified serial port, with the specified ID
	*
	* @param int ID, the Bus ID of the servo 1-255
	*/
	AX12(int ID, int baud = 1000000);
	
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
	
	/** Set goal angle in integer degrees, in positional mode
	*
	* @param degrees 0-300
	* @param flags, defaults to 0
	*    flags[0] = blocking, return when goal position reached
	*    flags[1] = register, activate with a broadcast trigger
	*
	*/
	int SetGoal(int degrees, int flags = 0);
	
	/** Set the speed of the servo
	*
	* If the mode is Joint
	* @param speed 0-1.0
	*    The unit is about 0.111rpm.
	*    If it is set to 0, it means the maximum rpm of the motor is used without controlling the speed.
	*    If it is 1023, it is about 114rpm.
	* If the mode is Wheel
	* @param speed, -1.0 to 1.0
	*   -1.0 = full speed counter clock wise
	*    1.0 = full speed clock wise
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
	
	/** Poll to see if the servo is moving
	*
	* @returns true is the servo is moving
	*/
	bool isMoving();
	
	/*Send the broadcast "trigger" command, to activate any outstanding registered commands
	*/
	void trigger();
	
	/** Read the current angle of the servo
	*
	* @returns float in the range 0.0-300.0
	*/
	float GetPosition();
	
	/** Read the current speed of the servo
	*
	* @returns float velocity
	*/
	float GetSpeed();
	
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
	
private:
	AX12();
	int read(int ID, int start, int bytes, char* data);
	int write(int ID, int start, int bytes, char* data, int flag);
	
private:
	int _ID;
	int _baud;
	Mode _mode;
	
	const int AX12_REG_ID  = 0x3;
	const int AX12_REG_BAUD = 0x4;
	const int AX12_REG_CW_LIMIT = 0x06;
	const int AX12_REG_CCW_LIMIT = 0x08;
	const int AX12_REG_GOAL_POSITION = 0x1E;
	const int AX12_REG_TORQUE_ENABLE = 0x18;
	const int AX12_REG_MOVING_SPEED = 0X20;
	const int AX12_REG_PRESENT_SPEED = 0x26;
	const int AX12_REG_VOLTS = 0x2A;
	const int AX12_REG_TEMP = 0x2B;
	const int AX12_REG_MOVING = 0x2E;
	const int AX12_REG_POSITION = 0x24;
	const int AX12_REG_SPEED = 0x26;
};

