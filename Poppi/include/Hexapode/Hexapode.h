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

#include "Leg.h"

#define LEG_COUNT 6

class Hexapode {
public:
	Hexapode();
	virtual ~Hexapode();
	virtual void initializeLegs();
	virtual void setDirection(Vector3 goal);

protected:
	Leg legs[LEG_COUNT];
	Vector3 m_direction;
};

#endif /* HEXAPODE_HEXAPODE_H_ */
