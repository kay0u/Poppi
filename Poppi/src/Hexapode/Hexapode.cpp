/*
 * Hexapode.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#include "../../include/Hexapode/Hexapode.h"

Hexapode::Hexapode():
m_tripodGait(m_legs),
m_position(Vector3::zero)
{
	initializeLegs();
	m_activeGait = &m_tripodGait;
	printf("TA MERE LA PUUUUUTE\r\n");

	for(int i(0);i < LEG_COUNT; ++i)
		m_legs[i] = new Leg();
}

Hexapode::~Hexapode()
{
	for(int i(0);i < LEG_COUNT; ++i)
		delete m_legs[i];
}

void Hexapode::initializeLegs()
{
	m_legs[0]->initRelativePosition(Vector3(0,0,0.5), 0);
	m_legs[1]->initRelativePosition(Vector3(0.454,0,0.214), -60);
	m_legs[2]->initRelativePosition(Vector3(0.414,0,-0.247), -120);
	m_legs[3]->initRelativePosition(Vector3(0,0,-0.5), -180);
	m_legs[4]->initRelativePosition(Vector3(-0.45,0,-0.25), -240);
	m_legs[5]->initRelativePosition(Vector3(-0.424,0,-0.259), -300);
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
