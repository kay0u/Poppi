/*
 * Servo.h
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_SERVO_H_
#define HEXAPODE_SERVO_H_

#include "../Math/Vector3.h"
#include "../../src/AX12.hpp"
#include "../../src/Uart.hpp"

class Servo {
public:
	Servo(float minAngle, float maxAngle);
	virtual ~Servo();
	void goTo(Vector3 pos);
	void stop();
	bool reachedTarget();

private:
	bool m_reachedTarget;
	const float m_minAngle;
	const float m_maxAngle;
};

#endif /* HEXAPODE_SERVO_H_ */
