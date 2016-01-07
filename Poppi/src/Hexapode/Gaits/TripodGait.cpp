/*
 * TripodGait.cpp
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#include "../../../include/Hexapode/Gaits/TripodGait.h"

TripodGait::TripodGait(Leg* (*legs)[LEG_COUNT]): Gait(legs)
{
	Movement mov0;
	mov0.push_back(LegStep(m_legs[0], End));
	mov0.push_back(LegStep(m_legs[1], End));
	mov0.push_back(LegStep(m_legs[2], End));
	mov0.push_back(LegStep(m_legs[3], End));
	mov0.push_back(LegStep(m_legs[4], End));
	mov0.push_back(LegStep(m_legs[5], End));

	Movement mov1;
	mov1.push_back(LegStep(m_legs[0], Idle));
	mov1.push_back(LegStep(m_legs[2], Idle));
	mov1.push_back(LegStep(m_legs[4], Idle));

	Movement mov2;
	mov2.push_back(LegStep(m_legs[0], Start));
	mov2.push_back(LegStep(m_legs[2], Start));
	mov2.push_back(LegStep(m_legs[4], Start));
	mov2.push_back(LegStep(m_legs[1], Idle));
	mov2.push_back(LegStep(m_legs[3], Idle));
	mov2.push_back(LegStep(m_legs[5], Idle));

	Movement mov3;
	mov3.push_back(LegStep(m_legs[0], End));
	mov3.push_back(LegStep(m_legs[2], End));
	mov3.push_back(LegStep(m_legs[4], End));

	Movement mov4;
	mov4.push_back(LegStep(m_legs[0], End));
	mov4.push_back(LegStep(m_legs[2], End));
	mov4.push_back(LegStep(m_legs[4], End));
	mov4.push_back(LegStep(m_legs[1], Idle));
	mov4.push_back(LegStep(m_legs[3], Idle));
	mov4.push_back(LegStep(m_legs[5], Idle));
}

TripodGait::~TripodGait()
{

}

void TripodGait::walk()
{

}

void TripodGait::update()
{
	if(stopped)
		return;
}
