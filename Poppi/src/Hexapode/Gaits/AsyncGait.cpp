/*
 * AsyncGait.cpp
 *
 *  Created on: 8 janv. 2016
 *      Author: Vincent
 */

#include <Hexapode/Gaits/AsyncGait.h>

AsyncGait::AsyncGait(std::array<Leg*, LEG_COUNT> &legs): Gait(legs)
{
	//mov0 mov1 et mov2 servent à l'initialisation
	m_moveLoopStart = 3;
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
	mov1.push_back(LegStep(m_legs[3], Idle));

	Movement mov2;
	mov2.push_back(LegStep(m_legs[0], Start));
	mov2.push_back(LegStep(m_legs[3], Start));
	mov2.push_back(LegStep(m_legs[1], Idle));
	mov2.push_back(LegStep(m_legs[4], Idle));

	//La boucle commence ici
	Movement mov3;
	mov3.push_back(LegStep(m_legs[0], End));
	mov3.push_back(LegStep(m_legs[3], End));
	mov3.push_back(LegStep(m_legs[1], Start));
	mov3.push_back(LegStep(m_legs[4], Start));
	mov3.push_back(LegStep(m_legs[2], Idle));
	mov3.push_back(LegStep(m_legs[5], Idle));

	Movement mov4;
	mov4.push_back(LegStep(m_legs[0], Idle));
	mov4.push_back(LegStep(m_legs[3], Idle));
	mov4.push_back(LegStep(m_legs[1], End));
	mov4.push_back(LegStep(m_legs[4], End));
	mov4.push_back(LegStep(m_legs[2], Start));
	mov4.push_back(LegStep(m_legs[5], Start));

	Movement mov5;
	mov5.push_back(LegStep(m_legs[0], Start));
	mov5.push_back(LegStep(m_legs[3], Start));
	mov5.push_back(LegStep(m_legs[1], Idle));
	mov5.push_back(LegStep(m_legs[4], Idle));
	mov5.push_back(LegStep(m_legs[2], End));
	mov5.push_back(LegStep(m_legs[5], End));

	m_movements.push_back(mov0);
	m_movements.push_back(mov1);
	m_movements.push_back(mov2);
	m_movements.push_back(mov3);
	m_movements.push_back(mov4);
	m_movements.push_back(mov5);
}

AsyncGait::~AsyncGait() {
	// TODO Auto-generated destructor stub
}
