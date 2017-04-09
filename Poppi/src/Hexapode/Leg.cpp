/*
 * Leg.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#include "Hexapode/Leg.h"

Leg::Leg(int startAxId) :
m_gamma(startAxId + 1, GAMMA_MINIMUM, GAMMA_MAXIMUM),
m_alpha(startAxId + 2, ALPHA_MINIMUM, ALPHA_MAXIMUM),
m_beta(startAxId + 3, BETA_MINIMUM, BETA_MAXIMUM),
m_tibiaLength(4),
m_femurLength(4),
m_coxaLength(0),
m_angleToHexapod(0),
m_speed(2),
m_gotoDirCenterPosition(Vector3(3, 0, -3))
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

	float distanceToTarget = Vector3::Distance(m_goal, Vector3(m_coxaLength, 0, 0));

	float alpha1 = acos(-m_goal.y / distanceToTarget);
	float alpha2 = acos((pow(m_tibiaLength, 2) - pow(m_femurLength, 2) - pow(distanceToTarget, 2)) / (-2 * m_femurLength * distanceToTarget));
	float beta1 = acos((pow(distanceToTarget, 2) - pow(m_tibiaLength, 2) - pow(m_femurLength, 2)) / (-2 * m_tibiaLength * m_femurLength));

	float gammaGoal = Trigo::Rad2Deg * atan2(m_goal.x, m_goal.z);
	float alphaGoal = -Trigo::Rad2Deg * (alpha1 + alpha2 - Trigo::Pi / 2);
	float betaGoal = Trigo::Rad2Deg * (-beta1 + Trigo::Pi);
	return Vector3(gammaGoal, alphaGoal, betaGoal);
}

void Leg::goToIK(Vector3 pos)
{
    Vector3 rots = processIK(pos);
    goToAngleIK(rots);
}

void Leg::goToAngleAx(Vector3 angles)
{
    m_gamma.goTo(angles.x);
    m_alpha.goTo(angles.y);
    m_beta.goTo(angles.z);
}

void Leg::goToAngleIK(Vector3 angles)
{
    m_gamma.goTo(angles.x + GAMMA_CENTER_OFFSET);
    m_alpha.goTo(angles.y + ALPHA_CENTER_OFFSET);
    m_beta.goTo(angles.z + BETA_CENTER_OFFSET);
}

void Leg::goTo(LegPosition pos)
{
	switch(pos)
	{
	case Idle:
		printf("Go to idle \n");
		goToIK(m_idlePosition);
		break;
	case Start:
		printf("Go to start \n");
		goToIK(m_startPosition);
		break;
	case End:
		printf("Go to end \n");
		goToIK(m_endPosition);
		break;
	}
}
