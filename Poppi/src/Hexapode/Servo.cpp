/*
 * Servo.cpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#include "Hexapode/Servo.h"
#include "UnitySerial.h"

Servo::Servo(int id, float minAngle, float maxAngle):
m_reachedTarget(true),
m_stopped(false),
m_maxAngle(maxAngle),
m_minAngle(minAngle),
m_axId(id),
m_ax(id),
m_isConnected(true),
m_epsilon(5) //Todo, à modifier
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
	angle = std::max(std::min(angle, m_maxAngle), m_minAngle);
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
	if (!m_isConnected)
		return true; //Todo: Pour l'instant, on dit que toutes les pattes sont branchées ok?!
	float goal;
	Error error; //Todo: Gérer les erreurs
	error = m_ax.GetGoalPosition(goal);
	if (error == Error::TIMEOUT)
	{
		m_isConnected = false;
		return true; //Todo: Pour l'instant, on dit que toutes les pattes sont branchées ok?!
	}
	float presentPosition;
	error = m_ax.GetPresentPosition(presentPosition);
	m_reachedTarget = std::abs(goal - presentPosition) < m_epsilon;  //On n'a jamais la même valeur en vrai
	return m_reachedTarget;
}

float Servo::getCurrentAngle()
{
	float angle;
	m_ax.GetPresentPosition(angle);
	return angle;
}