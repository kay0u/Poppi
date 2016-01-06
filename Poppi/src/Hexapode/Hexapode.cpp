/*
 * Hexapode.cpp
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#include "../../include/Hexapode/Hexapode.h"

Hexapode::Hexapode() {
	// TODO Auto-generated constructor stub

}

Hexapode::~Hexapode() {
	// TODO Auto-generated destructor stub
}

void Hexapode::initializeLegs()
{
    legs[0].initRelativePosition(Vector3(0,0,0.5), 0);
    legs[1].initRelativePosition(Vector3(0.454,0,0.214), -60);
    legs[2].initRelativePosition(Vector3(0.414,0,-0.247), -120);
    legs[3].initRelativePosition(Vector3(0,0,-0.5), -180);
    legs[4].initRelativePosition(Vector3(-0.45,0,-0.25), -240);
    legs[5].initRelativePosition(Vector3(-0.424,0,-0.259), -300);
}

void Hexapode::setDirection(Vector3 goal)
{
	m_direction = goal.normalized();
	for(int i(0); i < LEG_COUNT; ++i)
	{
		legs[i].setDirection(m_direction);
	}
}
