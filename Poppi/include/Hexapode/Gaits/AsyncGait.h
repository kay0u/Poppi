/*
 * AsyncGait.h
 *
 *  Created on: 8 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_GAITS_ASYNCGAIT_H_
#define HEXAPODE_GAITS_ASYNCGAIT_H_

#include "Gait.h"
#include "../../Useful.h"

class AsyncGait : public Gait
{
public:
	AsyncGait(std::array<Leg*, LEG_COUNT> &legs);
	virtual ~AsyncGait();
};

#endif /* HEXAPODE_GAITS_ASYNCGAIT_H_ */
