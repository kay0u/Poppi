/*
 * Hexapode.h
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 *
 *  Abstract class inherited by WalkingHexapode and RollingHexapodde
 */

#ifndef HEXAPODE_HEXAPODE_H_
#define HEXAPODE_HEXAPODE_H_

#include "../Useful.h"
#include "../Math/Vector3.h"

#include "Leg.h"
#include "Gaits/Gait.h"
#include "Gaits/TripodGait.h"

class Hexapode {
public:
	Hexapode();
	virtual ~Hexapode();
	void initializeLegs();
	void setDirection(Vector3 goal);
	void changeGait(Gait* newGait);
	void update();

protected:
	Leg* m_legs[LEG_COUNT];
	Vector3 m_direction;
	Vector3 m_position;

	//Gaits
	Gait* m_activeGait;
	TripodGait m_tripodGait;
};

#endif /* HEXAPODE_HEXAPODE_H_ */
