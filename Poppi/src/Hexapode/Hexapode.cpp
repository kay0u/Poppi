/*
 * Hexapode.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#include "Hexapode/Hexapode.h"

Hexapode::Hexapode():
m_position(Vector3::zero)
{
	for(int i(0);i < LEG_COUNT; ++i)
		m_legs[i] = new Leg(i*10);
	m_tripodGait = new TripodGait(m_legs);
	initializeLegs();
	m_activeGait  = m_tripodGait;
	setDirection(Vector3::zero);
}

Hexapode::~Hexapode()
{
	for(int i(0);i < LEG_COUNT; ++i)
		delete m_legs[i];
}

void Hexapode::initializeLegs()
{
	m_legs[0]->initRelativePosition(Vector3(0,0,4.95), 0);
	m_legs[1]->initRelativePosition(Vector3(4.54,0,2.14), -60);
	m_legs[2]->initRelativePosition(Vector3(4.14,0,-2.47), -120);
	m_legs[3]->initRelativePosition(Vector3(0,0,-5), -180);
	m_legs[4]->initRelativePosition(Vector3(-4.5,0,-2.5), -240);
	m_legs[5]->initRelativePosition(Vector3(-4.24,0, 2.59), -300);

	//m_legs[0]->goToAngleIK(Vector3(0, 0, 0));
}

void Hexapode::setDirection(Vector3 goal)
{
	m_direction = goal.normalized();
	m_activeGait->setDirection(m_direction);
}

void Hexapode::changeGait(Gait* newGait)
{
	m_activeGait = newGait;
	m_activeGait->init(m_direction);
}

void Hexapode::update()
{

}
