/*
 * TripodGait.h
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_GAITS_TRIPODGAIT_H_
#define HEXAPODE_GAITS_TRIPODGAIT_H_

#include "Gait.h"
#include "../../Useful.h"

class TripodGait : public Gait
{
public:
	TripodGait(std::array<Leg*, LEG_COUNT> &legs);
	virtual ~TripodGait();
};

#endif /* HEXAPODE_GAITS_TRIPODGAIT_H_ */
