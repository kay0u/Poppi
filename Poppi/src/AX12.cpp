#include "AX12.h"
#include "cmsis_os.h"
#include <algorithm>
#include "Useful.h"

template<typename serial>
AX12<serial>::AX12(int ID, int baud, Mode mode, bool shouldWaitForTrigger)
{
	_ID = ID;
	_baud = baud;
	_mode = mode;
	_shouldWaitForTrigger = shouldWaitForTrigger;
	serial::init(baud);
	serial::changeCommunicationMode(serial::communicationMode::TX);
	//SetMode(_mode);
}

template<typename serial>
AX12Base::Error AX12<serial>::read()
{
	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	{
		uint8_t test[20];
		for (int i = 0; i < _txBuf.size(); i++)
			test[i] = _txBuf[i];
	
		HAL_UART_Transmit(&serial::UART, test, _txBuf.size(), 100);
	}
	//serial::print(_txBuf);
	serial::waitEndTransmition();
	serial::changeCommunicationMode(serial::communicationMode::RX);
	
	// Skip if the read was to the broadcast address
	int ID = _txBuf[2];
	if(ID != ID_BROADCAST) {

		//printf("size : %d, capacity : %d", _rxBuf.size(), _rxBuf.capacity());
		// response packet is always 6 + bytes
		// 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
		// timeout is a little more than the time to transmit
		// the packet back, i.e. (6+bytes)*10 bit periods
		
		{
			uint8_t test[20];
	
			if (HAL_UART_Receive(&serial::UART, test, _rxBuf.size(), 1000) == HAL_OK)
			{
				if (_rxBuf.size() > 8)
					_rxBuf[0] = test[0];
				for (int i = 0; i < _rxBuf.size(); i++)
					_rxBuf[i] = test[i];
			}
			else
				return TIMEOUT;
		}
		/*if(serial::read(_rxBuf, 10) == serial::READ_TIMEOUT) {
			return TIMEOUT;
		}*/
		
		// Copy the data from Status into data for return
		for(int i = 0 ; i < std::min(_rxBuf[3] - 2, static_cast<int>(_rxBuf.size())); i++) {
			_data[i] = _rxBuf[5 + i];
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

	return static_cast<Error>(_rxBuf[4]);
}

template<typename serial>
AX12Base::Error AX12<serial>::write()
{
	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	{
		uint8_t test[20];
		for (int i = 0; i < _txBuf.size(); i++)
			test[i] = _txBuf[i];
	
		HAL_UART_Transmit(&serial::UART, test, _txBuf.size(), 100);
	}
	//serial::print(_txBuf);
	serial::waitEndTransmition();
	serial::changeCommunicationMode(serial::communicationMode::RX);
	
	// make sure we have a valid return
	_rxBuf[4] = 0x00;

	// we'll only get a reply if it was not broadcast
	int ID = _txBuf[2];
	if(ID != ID_BROADCAST) {
		
		_rxBuf[4] = 0xFE;  // return code

		// response packet is always 6 bytes
		// 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
		// timeout is a little more than the time to transmit
		// the packet back, i.e. 60 bit periods, round up to 100
		{
			uint8_t test[20];
			if (HAL_UART_Receive(&serial::UART, test, _rxBuf.size(), 1000) == HAL_OK)
			{
				for (int i = 0; i < _rxBuf.size(); i++)
					_rxBuf[i] = test[i];
			}
			else
				return TIMEOUT;
		}
		/*if(serial::read(_rxBuf, 10) == serial::READ_TIMEOUT) {
			return TIMEOUT;
		}*/
		
		
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
	
	Error error =  static_cast<Error>(_rxBuf[4]);
	
	return static_cast<Error>(_rxBuf[4]);
}

template<typename serial>
void AX12<serial>::trigger() {

	osMutexWait(mutex, osWaitForever);
	_txBuf.clear();
	char sum = 0;

#ifdef AX12_TRIGGER_DEBUG
	// Build the TxPacket first in RAM, then we'll send in one go
	serial_pc::printfln("Triggered");
	serial_pc::printfln("Trigger Packet");
	serial_pc::printfln("  Header : 0xFF, 0xFF");
#endif

	_txBuf.push_back(0xff);
	_txBuf.push_back(0xff);

	// ID - Broadcast
	_txBuf.push_back(0xFE);
	sum += _txBuf.back();

#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  ID : %d", _rxBuf[2]);
#endif

	// Length
	_txBuf.push_back(0x02);
	sum += _txBuf.back();

#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  Length %d", _rxBuf[3]);
#endif

	// Instruction - ACTION
	_txBuf.push_back(Instruction::ACTION);
	sum += _txBuf.back();

#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  Instruction 0x%X", _rxBuf[4]);
#endif

	// Checksum
	_txBuf.push_back(~sum);
#ifdef AX12_TRIGGER_DEBUG
	serial_pc::printfln("  Checksum 0x%X", _rxBuf[5]);
#endif

	// Transmit the packet in one burst with no pausing
	serial::changeCommunicationMode(serial::communicationMode::TX);
	serial::print(_txBuf);
		
	// This is a broadcast packet, so there will be no reply
	osMutexRelease(mutex);
	return;
}

template class AX12<serial_ax>;
template<typename serial> osMutexId AX12<serial>::mutex = osMutexCreate(osMutex(osmutex));
