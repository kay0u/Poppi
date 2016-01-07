/*
 * Gait.h
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_GAITS_GAIT_H_
#define HEXAPODE_GAITS_GAIT_H_

#include <vector>

#include "../../Useful.h"

#include "../Leg.h"
#include "../../Math/Vector3.h"

enum LegPosition {
	Idle,
	Start,
	End
};

struct LegStep {
	LegStep(Leg &leg, LegPosition position);

	Leg &leg;
	LegPosition position;
};
typedef std::vector<LegStep> Movement;

class Gait {
public:
	Gait(Leg* (*legs)[LEG_COUNT]);
	virtual ~Gait();

	virtual void setDirection(Vector3 direction);
	virtual void init(Vector3 direction);
	virtual void stop();
	virtual void update();
	virtual bool reachedTarget();

	//Abstracts
	virtual void walk() = 0;

protected:
	Leg* (*m_legs)[LEG_COUNT];
	Vector3 m_direction;
	bool stopped;
	std::vector<Movement> movements;
};

#endif /* HEXAPODE_GAITS_GAIT_H_ */
