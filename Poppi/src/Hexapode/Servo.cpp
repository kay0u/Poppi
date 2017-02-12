/*
 * Servo.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#include "../../include/Hexapode/Servo.h"

Servo::Servo(int id, float minAngle, float maxAngle):
m_reachedTarget(true),
m_maxAngle(maxAngle),
m_minAngle(minAngle),
m_ax(id)
{

}

Servo::~Servo()
{

}

void Servo::goTo(float angle)
{
	angle = fmax(fmin(angle, m_maxAngle), m_minAngle);
	printf("%f \n", angle);
	m_ax.SetGoalPosition(angle);
	printf("%f \n", angle);
}

void Servo::stop()
{

}

bool Servo::reachedTarget()
{
	return m_reachedTarget;
}
