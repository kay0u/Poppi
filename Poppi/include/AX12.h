#pragma once

#include "AX12Base.h"
#include <array>
#include "cmsis_os.h"

template<typename serial>
class AX12 : public AX12Base
{
public:	
	AX12() = delete;
	
	virtual ~AX12() {};
	
	/** Create an AX12 servo object connected to the specified serial port, with the specified ID
	*
	* @param int ID, the Bus ID of the servo 1-255
	*/
	AX12(int ID, int baud = 1000000, Mode mode = Mode::Join, bool shouldWaitForTrigger = false);
	
	/*Send the broadcast "trigger" command, to activate any outstanding registered commands
	*/
	void trigger();
	
	template <std::size_t size>
	void syncWriteGoalAndSpeed(const std::array<uint8_t, size>& idList, const std::array<int, size>& goalList, const std::array<float, size>& speedList);
	template <std::size_t size>
	void syncWriteGoal(const std::array<uint8_t, size>& idList, const std::array<int, size>& goalList);
	
protected:
	Error read() override;
	Error write() override;
	
private:
	static osMutexId mutex;
	
};

template<typename serial>
template <std::size_t size>
void AX12<serial>::syncWriteGoalAndSpeed(const std::array<uint8_t, size>& idList, const std::array<int, size>& goalList, const std::array<float, size>& speedList)
{
	_txBuf.clear();
	
	//REG_MOVING_SPEED is next to REG_GOAL_POSITION, so if you write after REG_GOAL_POSITION.address + REG_GOAL_POSITION.length, you write in REG_MOVING_SPEED.address
	int dataLength = REG_GOAL_POSITION.length + REG_MOVING_SPEED.length;
	int nbAX = idList.size();
	int length = (dataLength + 1) * nbAX + 4;  // (L + 1) X N + 4(L : Data Length per AX12, N : the number of AX12s)
	unsigned char sum = 0;
	
	_txBuf.push_back(0xFF);
	_txBuf.push_back(0xFF);
	
	//ID Broadcast
	_txBuf.push_back(0xFE);
	sum += _txBuf.back();
	
	_txBuf.push_back(length);
	sum += _txBuf.back();
	
	_txBuf.push_back(Instruction::SYNC_WRITE);
	sum += _txBuf.back();
	
	_txBuf.push_back(REG_GOAL_POSITION.address);
	sum += _txBuf.back();
	
	_txBuf.push_back(dataLength);
	sum += _txBuf.back();
	
	for (int i(0); i < idList.size(); i++)
	{
		_txBuf.push_back(idList[i]);
		sum += _txBuf.back();
		
		int angle = (1023 * goalList[i]) / 300;
		
		_txBuf.push_back(angle & 0xff);
		sum += _txBuf.back();
		
		_txBuf.push_back(angle >> 8);
		sum += _txBuf.back();
		
		int goal = (0x3ff * std::abs(speedList[i]));

		_txBuf.push_back(goal & 0xff);
		sum += _txBuf.back();
		
		_txBuf.push_back(goal >> 8);
		sum += _txBuf.back();
	}
	
	_txBuf.push_back(~sum);
	
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(_txBuf);
}

template<typename serial>
template <std::size_t size>
void AX12<serial>::syncWriteGoal(const std::array<uint8_t, size>& idList, const std::array<int, size>& goalList)
{
	_txBuf.clear();
	
	//REG_MOVING_SPEED is next to REG_GOAL_POSITION, so if you write after REG_GOAL_POSITION.address + REG_GOAL_POSITION.length, you write in REG_MOVING_SPEED.address
	int dataLength = REG_GOAL_POSITION.length/* + REG_MOVING_SPEED.length*/;
	int nbAX = idList.size();
	int length = (dataLength + 1) * nbAX + 4;  // (L + 1) X N + 4(L : Data Length per AX12, N : the number of AX12s)
	unsigned char sum = 0;
	
	_txBuf.push_back(0xFF);
	_txBuf.push_back(0xFF);
	
	//ID Broadcast
	_txBuf.push_back(0xFE);
	sum += _txBuf.back();
	
	_txBuf.push_back(length);
	sum += _txBuf.back();
	
	_txBuf.push_back(Instruction::SYNC_WRITE);
	sum += _txBuf.back();
	
	_txBuf.push_back(REG_GOAL_POSITION.address);
	sum += _txBuf.back();
	
	_txBuf.push_back(dataLength);
	sum += _txBuf.back();
	
	for (int i(0); i < idList.size(); i++)
	{
		_txBuf.push_back(idList[i]);
		sum += _txBuf.back();
		
		int angle = (1023 * goalList[i]) / 300;
		
		_txBuf.push_back(angle & 0xff);
		sum += _txBuf.back();
		
		_txBuf.push_back(angle >> 8);
		sum += _txBuf.back();
	}
	
	_txBuf.push_back(~sum);
	
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(_txBuf);
}

