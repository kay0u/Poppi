/*
 * Gait.h
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_GAITS_GAIT_H_
#define HEXAPODE_GAITS_GAIT_H_

#include <array>
#include <vector>

#include "FreeRTOS.h"
#include "task.h"

#include "../../Useful.h"

#include "LedController.h"
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
	Gait(std::array<Leg*, LEG_COUNT> &legs);
	virtual ~Gait();

	virtual void setDirection(Vector3 direction);
	virtual void init(Vector3 direction);
	virtual void stop();
	virtual void executeMovement(Movement move);
	virtual void waitForMoveEnd() const;
	virtual void walk();
	virtual bool isStopped();
	virtual std::vector<Movement>& getMovements();
	uint8_t getMoveLoopStart();
	void print() const;


protected:
	std::array<Leg*, LEG_COUNT> &m_legs;
	Vector3 m_direction;
	bool m_stopped;
	uint8_t m_moveLoopStart;
	std::vector<Movement> m_movements;
	TaskHandle_t m_taskHandle;
};

#endif /* HEXAPODE_GAITS_GAIT_H_ */
