/*
 * Leg.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#include "../../include/Hexapode/Leg.h"

Leg::Leg() :
m_femurLength(4),
m_tibiaLength(4),
m_angleToHexapod(0),
m_speed(2)
{

}

Leg::~Leg()
{

}

void Leg::initRelativePosition(Vector3 dist, float angle)
{
	m_distanceToHexapod = dist;
	m_angleToHexapod = Trigo::Deg2Rad * angle;
}

Vector3 Leg::hexapodSpaceToLocalSpace(Vector3 pos)
{
	Vector3 localPos;
	pos -= m_distanceToHexapod;
	localPos.x = cos(m_angleToHexapod) * pos.x + sin(m_angleToHexapod) * pos.z;
	localPos.z = cos(m_angleToHexapod) * pos.z - sin(m_angleToHexapod) * pos.x;
	localPos.y = pos.y;

	return localPos;
}

void Leg::setDirection(Vector3 dir)
{
	m_startPosition = hexapodSpaceToLocalSpace(m_gotoDirCenterPosition + dir * m_speed);
	m_endPosition = hexapodSpaceToLocalSpace(m_gotoDirCenterPosition - dir * m_speed);
	m_idlePosition = hexapodSpaceToLocalSpace(m_gotoDirCenterPosition + Vector3(0, 3, 0));
}

void Leg::stop()
{
	m_gamma.stop();
	m_alpha.stop();
	m_beta.stop();
}

bool Leg::hasReachedGoal()
{
	return (m_gamma.reachedTarget() && m_alpha.reachedTarget() && m_beta.reachedTarget());
}

Vector3 Leg::processIK(Vector3 pos)
{
	m_goal = pos;

	float distanceToTarget = Vector3::Distance(m_goal, Vector3::zero);

	float alpha1 = acos(-m_goal.y / distanceToTarget);
	float alpha2 = acos((pow(m_tibiaLength, 2) - pow(m_femurLength, 2) - pow(distanceToTarget, 2)) / (-2 * m_femurLength * distanceToTarget));
	float beta1 = acos((pow(distanceToTarget, 2) - pow(m_tibiaLength, 2) - pow(m_femurLength, 2)) / (-2 * m_tibiaLength * m_femurLength));

	float gammaGoal = Trigo::Rad2Deg * atan2(m_goal.x, m_goal.z);
	float alphaGoal = -Trigo::Rad2Deg * (alpha1 + alpha2 - Trigo::Pi / 2);
	float betaGoal = Trigo::Rad2Deg * (-beta1 + Trigo::Pi);
	return Vector3(gammaGoal, alphaGoal, betaGoal);
}

void Leg::goTo(Vector3 pos)
{
    Vector3 rots = processIK(pos);

    m_gamma.goTo(Vector3(0, rots.x, 0));
    m_alpha.goTo(Vector3(rots.y, 0, 0));
    m_beta.goTo(Vector3(rots.z, 0, 0));
}
