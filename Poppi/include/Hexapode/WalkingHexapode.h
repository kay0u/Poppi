/*
 * WalkingHexapode.h
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_WALKINGHEXAPODE_H_
#define HEXAPODE_WALKINGHEXAPODE_H_

#include "Hexapode.h"

class WalkingHexapode : public Hexapode
{
public:
	WalkingHexapode();
	virtual ~WalkingHexapode();
	virtual void initializeLegs();
};

#endif /* HEXAPODE_WALKINGHEXAPODE_H_ */
