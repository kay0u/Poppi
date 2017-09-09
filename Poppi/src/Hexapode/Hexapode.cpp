/*
 * Hexapode.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#include "Hexapode/Hexapode.h"

Hexapode::Hexapode():
m_position(Vector3::zero),
m_direction(Vector3::zero)
{
	for(int i(0);i < LEG_COUNT; ++i)
		m_legs[i] = new Leg(i*10);
	m_tripodGait = new TripodGait(m_legs);
	initializeLegs();
	m_activeGait  = m_tripodGait;
	//setDirection(Vector3::zero);
}

Hexapode::~Hexapode()
{
	for(int i(0);i < LEG_COUNT; ++i)
		delete m_legs[i];
	delete m_tripodGait;
}

void Hexapode::initializeLegs()
{
	//Positions récupérées d'unity
	m_legs[0]->initRelativePosition(Vector3(8.55,0,34.81), 0);
	m_legs[1]->initRelativePosition(Vector3(13.09, 0, 32), -60);
	m_legs[2]->initRelativePosition(Vector3(12.69, 0, 27.39), -120);
	m_legs[3]->initRelativePosition(Vector3(8.55, 0, 24.86), -180);
	m_legs[4]->initRelativePosition(Vector3(4.05, 0, 27.36), -240);
	m_legs[5]->initRelativePosition(Vector3(4.31,0,32.45), -300);

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
