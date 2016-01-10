/*
 * Gait.cpp
 *
 *  Created on: 7 janv. 2016
 *      Author: Vincent
 */

#include "Useful.h"
#include "Hexapode/Gaits/Gait.h"

Gait::Gait(Leg* (&legs)[LEG_COUNT]):
m_legs(legs),
m_direction(Vector3::zero),
m_stopped(true),
m_moveLoopStart(0)
{
	osMutexDef(osMutex);
	m_mutexId = osMutexCreate(osMutex(osMutex));
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
	printDebug("[Gait] setDirection\n\r");
	m_direction = goal;
	osMutexWait(m_mutexId, 0);
	for(int i(0); i < LEG_COUNT; ++i)
		m_legs[i]->setDirection(goal);
	osMutexRelease(m_mutexId);

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
	m_stopped = true;
	osThreadTerminate(m_moveThreadId);
}

void Gait::print() const
{
	printf("%i\r\n", m_stopped);
}

void walkThread(void const *argument)
{
	//const Gait* gait = static_cast<const Gait*>(argument);
	/*std::vector<Movement>& movements = gait->getMovements();
	printDebug("[Gait] walkThread %i\n\r", movements.size());
	gait->executeMovement(movements[0]);
	printDebug("[Gait] walkThread\n\r");
	uint8_t loopStartIndex = gait->getMoveLoopStart();*/
	//gait->print();
	for(;;)
	{
		//for(uint32_t i(loopStartIndex); i < movements.size(); ++i)
		{
			//gait->executeMovement(movements[i]);
			//gait->waitForMoveEnd();
			osDelay(1000);
			LedController::Instance().toggleAllLed();
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
	osThreadDef(WalkThread, walkThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	m_moveThreadId = osThreadCreate(osThread(WalkThread), (void*)this);
}

void Gait::executeMovement(Movement move)
{
	osMutexWait(m_mutexId, 0);
	for(uint32_t i(0); i < move.size(); ++i)
		move[i].leg->goTo(move[i].position);
	osMutexRelease(m_mutexId);
}

void Gait::waitForMoveEnd() const
{
	osMutexWait(m_mutexId, 0);
	osDelay(1000);
	LedController::Instance().toggleLed(LedRed);
	osMutexRelease(m_mutexId);
}

bool Gait::isStopped()
{
	return m_stopped;
}
