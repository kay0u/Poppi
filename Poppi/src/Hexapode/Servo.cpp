/*
 * Servo.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#include "../../include/Hexapode/Servo.h"
#include "../UnitySerial.h"

Servo::Servo(int id, float minAngle, float maxAngle):
m_reachedTarget(true),
m_stopped(false),
m_maxAngle(maxAngle),
m_minAngle(minAngle),
m_axId(id),
m_ax(id)
{
}

Servo::~Servo()
{

}

void Servo::goTo(float angle)
{
	if (m_stopped)
	{
		m_ax.SetTorque(true);
		m_stopped = false;
	}
	angle = fmax(fmin(angle, m_maxAngle), m_minAngle);
	m_ax.SetGoalPosition(angle);
	UnitySerial::SendAx12GoToPosition(m_axId, angle);
}

float Servo::getMaxAngle()
{
	return m_maxAngle;
}

float Servo::getMinAngle()
{
	return m_minAngle;
}

void Servo::stop()
{
	m_ax.SetTorque(false);
	m_stopped = true;
}

bool Servo::reachedTarget()
{
	return m_reachedTarget;
}

float Servo::getCurrentAngle()
{
	return m_ax.GetPresentPosition();
}