/*
 * Servo.h
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_SERVO_H_
#define HEXAPODE_SERVO_H_

#include "../Math/Vector3.h"

class Servo {
public:
	Servo();
	virtual ~Servo();
	void goTo(Vector3 pos);
	void stop();
	bool reachedTarget();

private:
	bool m_reachedTarget;
};

#endif /* HEXAPODE_SERVO_H_ */
