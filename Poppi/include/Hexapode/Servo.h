/*
 * Servo.h
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */


#ifndef HEXAPODE_SERVO_H_
#define HEXAPODE_SERVO_H_

#include <math.h>
#include "Math/Vector3.h"
#include "Useful.h"
#include "AX12.h"

class Servo {
public:
	Servo(int id, float minAngle, float maxAngle);
	virtual ~Servo();
	void goTo(float angle);
	void stop();
	bool reachedTarget();
	float getMaxAngle();
	float getMinAngle();
	
private:
	AX12<serial_ax> m_ax;
	bool m_reachedTarget;
	const float m_minAngle;
	const float m_maxAngle;
	const int m_axId;
};

#endif /* HEXAPODE_SERVO_H_ */
