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

struct LegStep {
	LegStep(Leg *leg, LegPosition position);

	Leg *leg;
	LegPosition position;
};
typedef std::vector<LegStep> Movement;

class Gait {
public:
	Gait(Leg* (&legs)[LEG_COUNT]);
	virtual ~Gait();

	virtual void setDirection(Vector3 direction);
	virtual void init(Vector3 direction);
	virtual void stop();
	virtual void executeMovement(Movement move);
	virtual void waitForMoveEnd();
	virtual void walk();
	virtual bool isStopped();
	virtual std::vector<Movement>& getMovements();

protected:
	Leg* (&m_legs)[LEG_COUNT];
	Vector3 m_direction;
	bool m_stopped;
	std::vector<Movement> m_movements;
	osThreadId m_moveThreadId;
	osMutexId m_mutexId;
};

#endif /* HEXAPODE_GAITS_GAIT_H_ */
