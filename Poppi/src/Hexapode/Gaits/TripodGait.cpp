/*
 * TripodGait.cpp
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#include "Hexapode/Gaits/TripodGait.h"

TripodGait::TripodGait(std::array<Leg*, LEG_COUNT> &legs): Gait(legs)
{
	//mov0 sert à l'initialisation
	m_moveLoopStart = 1;
	Movement mov0;
	mov0.push_back(LegStep(m_legs[0], End));
	mov0.push_back(LegStep(m_legs[1], End));
	mov0.push_back(LegStep(m_legs[2], End));
	mov0.push_back(LegStep(m_legs[3], End));
	mov0.push_back(LegStep(m_legs[4], End));
	mov0.push_back(LegStep(m_legs[5], End));

	//La boucle commence ici
	Movement mov1;
	mov1.push_back(LegStep(m_legs[0], Idle));
	mov1.push_back(LegStep(m_legs[2], Idle));
	mov1.push_back(LegStep(m_legs[4], Idle));
	mov1.push_back(LegStep(m_legs[1], End));
	mov1.push_back(LegStep(m_legs[3], End));
	mov1.push_back(LegStep(m_legs[5], End));

	Movement mov2;
	mov2.push_back(LegStep(m_legs[0], Start));
	mov2.push_back(LegStep(m_legs[2], Start));
	mov2.push_back(LegStep(m_legs[4], Start));

	Movement mov3;
	mov3.push_back(LegStep(m_legs[1], Idle));
	mov3.push_back(LegStep(m_legs[3], Idle));
	mov3.push_back(LegStep(m_legs[5], Idle));

	Movement mov4;
	mov4.push_back(LegStep(m_legs[0], End));
	mov4.push_back(LegStep(m_legs[2], End));
	mov4.push_back(LegStep(m_legs[4], End));
	mov4.push_back(LegStep(m_legs[1], Start));
	mov4.push_back(LegStep(m_legs[3], Start));
	mov4.push_back(LegStep(m_legs[5], Start));

	m_movements.push_back(mov0);
	m_movements.push_back(mov1);
	m_movements.push_back(mov2);
	m_movements.push_back(mov3);
	m_movements.push_back(mov4);
}

TripodGait::~TripodGait()
{

}
