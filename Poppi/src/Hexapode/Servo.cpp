/*
 * Servo.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#include "../../include/Hexapode/Servo.h"

Servo::Servo(float minAngle, float maxAngle):
m_reachedTarget(true),
m_maxAngle(maxAngle),
m_minAngle(minAngle)
{
	// TODO Auto-generated constructor stub

}

Servo::~Servo() {
	// TODO Auto-generated destructor stub
}

void Servo::goTo(Vector3 pos)
{
	printf("(%f, %f, %f)\n", pos.x, pos.y, pos.z);
}

void Servo::stop()
{

}

bool Servo::reachedTarget()
{
	return m_reachedTarget;
}
