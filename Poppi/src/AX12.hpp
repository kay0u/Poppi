/*
 * AX12.h
 *
 *  Created on: 20 déc. 2015
 *      Author: Pierre
 */

#ifndef AX12_H_
#define AX12_H_

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include <math.h>

#define UNITY

#define AX12_REG_ID 0x3
#define AX12_REG_BAUD 0x4
#define AX12_REG_CW_LIMIT 0x06
#define AX12_REG_CCW_LIMIT 0x08
#define AX12_REG_GOAL_POSITION 0x1E
#define AX12_REG_TORQUE_ENABLE 0x18
#define AX12_REG_MOVING_SPEED 0x20
#define AX12_REG_VOLTS 0x2A
#define AX12_REG_TEMP 0x2B
#define AX12_REG_MOVING 0x2E
#define AX12_REG_POSITION 0x24

#define AX12_MODE_POSITION  0
#define AX12_MODE_ROTATION  1

#define AX12_CW 1
#define AX12_CCW

template<typename serial>
class AX12 {
private:
	AX12();
	//TODO IDK
	//virtual ~AX12();
    int _ID;
    int _baud;

public:

    /** Create an AX12 servo object connected to the specified serial port, with the specified ID
     *
     * @param int ID, the Bus ID of the servo 1-255
     */
    AX12(int ID, int baud = 1000000) {
        _ID = ID;
        _baud = baud;
        serial::changeCommunicationMode(serial::communicationMode::TX);
    }

    /** Set the mode of the servo
     * @param mode
     *    0 = Positional, default
     *    1 = Continuous rotation
     */
    int SetMode(int mode) {

        if (mode == 1) { // set CR
            SetCWLimit(0);
            SetCCWLimit(0);
            SetCRSpeed(0.0);
        } else {
            SetCWLimit(0);
            SetCCWLimit(300);
            SetCRSpeed(0.0);
        }
        return(0);
    }

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
    int SetBaud (int baud) {

    	//TODO: check
    	int flag = 0;
        char data[1];
        data[0] = baud;

    #ifdef AX12_DEBUG
        printf("Setting Baud rate to %d\n",baud);
    #endif

        return (write(0xFE, AX12_REG_BAUD, 1, data, flag));

    }


    /** Set goal angle in integer degrees, in positional mode
     *
     * @param degrees 0-300
     * @param flags, defaults to 0
     *    flags[0] = blocking, return when goal position reached
     *    flags[1] = register, activate with a broadcast trigger
     *
     */
    int SetGoal(int degrees, int flags = 0) {

        char reg_flag = 0;
        char data[2];

        // set the flag is only the register bit is set in the flag
        if (flags == 0x2) {
            reg_flag = 1;
        }

        // 1023 / 300 * degrees
        short goal = (1023 * degrees) / 300;
    #ifdef AX12_DEBUG
        printf("SetGoal to 0x%x\n",goal);
    #endif

        data[0] = goal & 0xff; // bottom 8 bits
        data[1] = goal >> 8;   // top 8 bits

        // write the packet, return the error code
        int rVal = write(_ID, AX12_REG_GOAL_POSITION, 2, data, reg_flag);
#ifdef UNITY
        Uart<1>::printfln("move %d %d", _ID, degrees);
#endif
        if (flags == 1) {
            // block until it comes to a halt
            while (isMoving()) {}
        }
        return(rVal);
    }


    /** Set the speed of the servo in continuous rotation mode
     *
     * @param speed, -1.0 to 1.0
     *   -1.0 = full speed counter clock wise
     *    1.0 = full speed clock wise
     */
    int SetCRSpeed(float speed) {

    	//TODO: check
    	int flag = 0;

        // bit 10     = direction, 0 = CCW, 1=CW
        // bits 9-0   = Speed
        char data[2];

        int goal = (0x3ff * fabs(speed));

        // Set direction CW if we have a negative speed
        if (speed < 0) {
            goal |= (0x1 << 10);
        }

        data[0] = goal & 0xff; // bottom 8 bits
        data[1] = goal >> 8;   // top 8 bits

        // write the packet, return the error code
        int rVal = write(_ID, 0x20, 2, data, flag);

        return(rVal);
    }


    /** Set the clockwise limit of the servo
     *
     * @param degrees, 0-300
     */
    int SetCWLimit (int degrees) {

    	//TODO: check
    	int flag = 0;

    	char data[2];

        // 1023 / 300 * degrees
        short limit = (1023 * degrees) / 300;

    #ifdef AX12_DEBUG
        printf("SetCWLimit to 0x%x\n",limit);
    #endif

        data[0] = limit & 0xff; // bottom 8 bits
        data[1] = limit >> 8;   // top 8 bits

        // write the packet, return the error code
        return (write(_ID, AX12_REG_CW_LIMIT, 2, data, flag));

    }

    /** Set the counter-clockwise limit of the servo
     *
     * @param degrees, 0-300
     */
    int SetCCWLimit (int degrees) {

    	//TODO: check
    	int flag = 0;

        char data[2];

        // 1023 / 300 * degrees
        short limit = (1023 * degrees) / 300;

    #ifdef AX12_DEBUG
        printf("SetCCWLimit to 0x%x\n",limit);
    #endif

        data[0] = limit & 0xff; // bottom 8 bits
        data[1] = limit >> 8;   // top 8 bits

        // write the packet, return the error code
        return (write(_ID, AX12_REG_CCW_LIMIT, 2, data, flag));
    }

    // Change the ID

    /** Change the ID of a servo
     *
     * @param CurentID 1-255
     * @param NewID 1-255
     *
     * If a servo ID is not know, the broadcast address of 0 can be used for CurrentID.
     * In this situation, only one servo should be connected to the bus
     */
    int SetID (int CurrentID, int NewID) {

    	//TODO: check
    	int flag = 0;

        char data[1];
        data[0] = NewID;

    #ifdef AX12_DEBUG
        printf("Setting ID from 0x%x to 0x%x\n",CurrentID,NewID);
    #endif
        _ID = CurrentID;
        //TODO: catch error
        return (write(CurrentID, AX12_REG_ID, 1, data, flag));

    }


    /** Poll to see if the servo is moving
     *
     * @returns true is the servo is moving
     */
    int isMoving(void) {

        char data[1];
        read(_ID,AX12_REG_MOVING,1,data);
        return(data[0]);
    }

    /** Send the broadcast "trigger" command, to activate any outstanding registered commands
     */
    void trigger(void) {

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
        printf("  ID : %d\n",TxBuf[2]);
    #endif

        // Length
        TxBuf[3] = 0x02;
        sum += TxBuf[3];

    #ifdef AX12_TRIGGER_DEBUG
        printf("  Length %d\n",TxBuf[3]);
    #endif

        // Instruction - ACTION
        TxBuf[4] = 0x04;
        sum += TxBuf[4];

    #ifdef AX12_TRIGGER_DEBUG
        printf("  Instruction 0x%X\n",TxBuf[5]);
    #endif

        // Checksum
        TxBuf[5] = 0xFF - sum;
    #ifdef AX12_TRIGGER_DEBUG
        printf("  Checksum 0x%X\n",TxBuf[5]);
    #endif

        // Transmit the packet in one burst with no pausing
	    serial::print(TxBuf, 6);

        // This is a broadcast packet, so there will be no reply
        return;
    }

    /** Read the current angle of the servo
     *
     * @returns float in the range 0.0-300.0
     */
    float GetPosition(void) {

#ifdef AX12_DEBUG
    printf("\nGetPosition(%d)",_ID);
#endif

    char data[2];

    int ErrorCode = read(_ID, AX12_REG_POSITION, 2, data);
    short position = data[0] + (data[1] << 8);
    float angle = (position * 300)/1024;

    return (angle);
}

    /** Read the temperature of the servo
     *
     * @returns float temperature
     */
    float GetTemp (void) {

#ifdef AX12_DEBUG
    printf("\nGetTemp(%d)",_ID);
#endif

    char data[1];
    int ErrorCode = read(_ID, AX12_REG_TEMP, 1, data);
    float temp = data[0];
    return(temp);
}

    /** Read the supply voltage of the servo
     *
     * @returns float voltage
     */
    float GetVolts (void) {

#ifdef AX12_DEBUG
    printf("\nGetVolts(%d)",_ID);
#endif

    char data[1];
    int ErrorCode = read(_ID, AX12_REG_VOLTS, 1, data);
    float volts = data[0]/10.0;
    return(volts);
}

private:
    int read(int ID, int start, int bytes, char* data) {

        char PacketLength = 0x4;
        char TxBuf[16];
        char sum = 0;
        char Status[16];

        Status[4] = 0xFE; // return code

    #ifdef AX12_READ_DEBUG
        printf("\nread(%d,0x%x,%d,data)\n",ID,start,bytes);
    #endif

        // Build the TxPacket first in RAM, then we'll send in one go
    #ifdef AX12_READ_DEBUG
        printf("\nInstruction Packet\n  Header : 0xFF, 0xFF\n");
    #endif

        TxBuf[0] = 0xff;
        TxBuf[1] = 0xff;

        // ID
        TxBuf[2] = ID;
        sum += TxBuf[2];

    #ifdef AX12_READ_DEBUG
        printf("  ID : %d\n",TxBuf[2]);
    #endif

        // Packet Length
        TxBuf[3] = PacketLength;    // Length = 4 ; 2 + 1 (start) = 1 (bytes)
        sum += TxBuf[3];            // Accululate the packet sum

    #ifdef AX12_READ_DEBUG
        printf("  Length : 0x%x\n",TxBuf[3]);
    #endif

        // Instruction - Read
        TxBuf[4] = 0x2;
        sum += TxBuf[4];

    #ifdef AX12_READ_DEBUG
        printf("  Instruction : 0x%x\n",TxBuf[4]);
    #endif

        // Start Address
        TxBuf[5] = start;
        sum += TxBuf[5];

    #ifdef AX12_READ_DEBUG
        printf("  Start Address : 0x%x\n",TxBuf[5]);
    #endif

        // Bytes to read
        TxBuf[6] = bytes;
        sum += TxBuf[6];

    #ifdef AX12_READ_DEBUG
        printf("  No bytes : 0x%x\n",TxBuf[6]);
    #endif

        // Checksum
        TxBuf[7] = 0xFF - sum;
    #ifdef AX12_READ_DEBUG
        printf("  Checksum : 0x%x\n",TxBuf[7]);
    #endif

        // Transmit the packet in one burst with no pausing
	    serial::print(TxBuf, 8);

        // Wait for the bytes to be transmitted
        //TODO check
        osDelay(2);

        // Skip if the read was to the broadcast address
        if (_ID != 0xFE) {

        	//TODO check
            serial::changeCommunicationMode(serial::communicationMode::RX);


            // response packet is always 6 + bytes
            // 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
            // timeout is a little more than the time to transmit
            // the packet back, i.e. (6+bytes)*10 bit periods

            int timeout = 0;
            int plen = 0;
            while ((timeout < ((6+bytes)*10)) && (plen<(6+bytes))) {

                if (serial::available()) {
                	serial::read_char(Status[plen]);
                    plen++;
                    timeout = 0;
                }

                // wait for the bit period
                //TODO check
                osDelay (1000.0/_baud);
                timeout++;
            }

            //TODO check
            serial::changeCommunicationMode(serial::communicationMode::TX);

            if (timeout == ((6+bytes)*10) ) {
                return(-1);
            }

            // Copy the data from Status into data for return
            for (int i=0; i < Status[3]-2 ; i++) {
                data[i] = Status[5+i];
            }

    #ifdef AX12_READ_DEBUG
            printf("\nStatus Packet\n");
            printf("  Header : 0x%x\n",Status[0]);
            printf("  Header : 0x%x\n",Status[1]);
            printf("  ID : 0x%x\n",Status[2]);
            printf("  Length : 0x%x\n",Status[3]);
            printf("  Error Code : 0x%x\n",Status[4]);

            for (int i=0; i < Status[3]-2 ; i++) {
                printf("  Data : 0x%x\n",Status[5+i]);
            }

            printf("  Checksum : 0x%x\n",Status[5+(Status[3]-2)]);
    #endif

        } // if (ID!=0xFE)

        return(Status[4]);
    }

    int write(int ID, int start, int bytes, char* data, int flag) {
    	// 0xff, 0xff, ID, Length, Intruction(write), Address, Param(s), Checksum

    	    char TxBuf[16];
    	    char sum = 0;
    	    char Status[6];

    	#ifdef AX12_WRITE_DEBUG
    	    printf("\nwrite(%d,0x%x,%d,data,%d)\n",ID,start,bytes,flag);
    	#endif

    	    // Build the TxPacket first in RAM, then we'll send in one go
    	#ifdef AX12_WRITE_DEBUG
    	    printf("\nInstruction Packet\n  Header : 0xFF, 0xFF\n");
    	#endif

    	    TxBuf[0] = 0xff;
    	    TxBuf[1] = 0xff;

    	    // ID
    	    TxBuf[2] = ID;
    	    sum += TxBuf[2];

    	#ifdef AX12_WRITE_DEBUG
    	    printf("  ID : %d\n",TxBuf[2]);
    	#endif

    	    // packet Length
    	    TxBuf[3] = 3+bytes;
    	    sum += TxBuf[3];

    	#ifdef AX12_WRITE_DEBUG
    	    printf("  Length : %d\n",TxBuf[3]);
    	#endif

    	    // Instruction
    	    if (flag == 1) {
    	        TxBuf[4]=0x04;
    	        sum += TxBuf[4];
    	    } else {
    	        TxBuf[4]=0x03;
    	        sum += TxBuf[4];
    	    }

    	#ifdef AX12_WRITE_DEBUG
    	    printf("  Instruction : 0x%x\n",TxBuf[4]);
    	#endif

    	    // Start Address
    	    TxBuf[5] = start;
    	    sum += TxBuf[5];

    	#ifdef AX12_WRITE_DEBUG
    	    printf("  Start : 0x%x\n",TxBuf[5]);
    	#endif

    	    // data
    	    for (char i=0; i<bytes ; i++) {
    	        TxBuf[6+i] = data[i];
    	        sum += TxBuf[6+i];

    	#ifdef AX12_WRITE_DEBUG
    	        printf("  Data : 0x%x\n",TxBuf[6+i]);
    	#endif

    	    }

    	    // checksum
    	    TxBuf[6+bytes] = 0xFF - sum;

    	#ifdef AX12_WRITE_DEBUG
    	    printf("  Checksum : 0x%x\n",TxBuf[6+bytes]);
    	#endif

    	    // Transmit the packet in one burst with no pausing
    	    serial::print(TxBuf, 7 + bytes);

    	    // Wait for data to transmit
            //TODO check
            osDelay(2);

    	    // make sure we have a valid return
    	    Status[4]=0x00;

    	    // we'll only get a reply if it was not broadcast
    	    if (_ID!=0xFE) {

    	    	//TODO check
    	        serial::changeCommunicationMode(serial::communicationMode::RX);

    	        // response packet is always 6 bytes
    	        // 0xFF, 0xFF, ID, Length Error, Param(s) Checksum
    	        // timeout is a little more than the time to transmit
    	        // the packet back, i.e. 60 bit periods, round up to 100
    	        int timeout = 0;
    	        int plen = 0;
    	        while ((timeout < 100) && (plen<6)) {

    	            if (serial::available()) {
    	            	serial::read_char(Status[plen]);
    	                plen++;
    	                timeout = 0;
    	            }

    	            // wait for the bit period
                    //TODO check
                    osDelay (1000.0/_baud);
    	            timeout++;
    	        }

    	        //TODO check
    	        serial::changeCommunicationMode(serial::communicationMode::TX);

    	        // Build the TxPacket first in RAM, then we'll send in one go
    	#ifdef AX12_WRITE_DEBUG
    	        printf("\nStatus Packet\n  Header : 0x%X, 0x%X\n",Status[0],Status[1]);
    	        printf("  ID : %d\n",Status[2]);
    	        printf("  Length : %d\n",Status[3]);
    	        printf("  Error : 0x%x\n",Status[4]);
    	        printf("  Checksum : 0x%x\n",Status[5]);
    	#endif


    	    }

    	    return(Status[4]); // return error code
    	}

};

#endif /* AX12_H_ */
