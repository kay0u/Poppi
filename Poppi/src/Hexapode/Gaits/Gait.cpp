/*
 * Gait.cpp
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#include "Useful.h"
#include "Hexapode/Gaits/Gait.h"

osMutexId mutex = NULL;
osMutexDef(gaitMutex);

Gait::Gait(std::array<Leg*, LEG_COUNT> &legs):
m_legs(legs),
m_direction(Vector3::zero),
m_stopped(true),
m_moveLoopStart(0)
{
	m_taskHandle = NULL;
	mutex = osMutexCreate(osMutex(gaitMutex));
}

LegStep::LegStep(Leg *l, LegPosition pos):
		leg(l)
{
	position = pos;
}

Gait::~Gait()
{

}

void Gait::setDirection(Vector3 goal)
{
	printf("[Gait] setDirection\n\r");
	m_direction = goal;
	for(int i(0); i < LEG_COUNT; ++i)
		m_legs[i]->setDirection(goal);

	m_stopped = m_direction == Vector3::zero;

	if(!m_stopped)
		walk();
}

void Gait::init(Vector3 direction)
{
	m_direction = direction;
}

void Gait::stop()
{
	m_direction = Vector3::zero;
	m_stopped = false;
}

void Gait::print() const
{
	printf("%i\r\n", m_stopped);
}

void walkTask(void *argument)
{
		if( osMutexWait(mutex, osWaitForever) == osOK )
		{
			Gait* gait = static_cast<Gait*>(argument);
			std::vector<Movement> &movements = gait->getMovements();
			uint8_t loopStartIndex = gait->getMoveLoopStart();
            osMutexRelease(mutex);

			for(uint8_t i(0); i < movements.size() && i < loopStartIndex; ++i)
			{
				if (osMutexWait(mutex, osWaitForever) == osOK)
				{
					gait->executeMovement(movements[i]);
					gait->waitForMoveEnd();
					osMutexRelease(mutex);
				}
			}

            for(;;)
			{
				for(uint8_t i(loopStartIndex); i < movements.size(); ++i)
				{
					if (osMutexWait(mutex, osWaitForever) == osOK)
					{
						gait->executeMovement(movements[i]);
						gait->waitForMoveEnd();
						osMutexRelease(mutex);
					}
				}
			}
		}
}

std::vector<Movement>& Gait::getMovements()
{
	return m_movements;
}

uint8_t Gait::getMoveLoopStart()
{
	return m_moveLoopStart;
}

void Gait::walk()
{
	LedController::Instance().toggleAllLed();
	xTaskCreate(walkTask, "Walk task", configMINIMAL_STACK_SIZE + 200, this, osPriorityNormal,&m_taskHandle);
	configASSERT(m_taskHandle);
}

void Gait::executeMovement(Movement move)
{
	for(uint32_t i(0); i < move.size(); ++i)
		move[i].leg->goTo(move[i].position);
}

void Gait::waitForMoveEnd() const
{
	osDelay(1000);
}

bool Gait::isStopped()
{
	return m_stopped;
}