/*
 * Leg.h
 *
 *  Created on: 6 janv. 2016
 *      Author: Vincent
 */

#ifndef HEXAPODE_LEG_H_
#define HEXAPODE_LEG_H_

#include <math.h>

#include "Servo.h"

#include "../Math/Vector3.hpp"
#include "../Math/Trigo.hpp"

class Leg {
public:
	Leg();
	virtual ~Leg();
	void initRelativePosition(Vector3 dist, float angle);
	Vector3 hexapodSpaceToLocalSpace(Vector3 pos);
	void setDirection(Vector3 dir);
	void stop();
	bool hasReachedGoal();
	Vector3 processIK(Vector3 pos);
	void goTo(Vector3 pos);
private:
	//Servos
	Servo m_gamma;
	Servo m_alpha;
	Servo m_beta;

	//Geometry
	const float m_tibiaLength;
	const float m_femurLength;
	float m_angleToHexapod;

	//Kinematic
	float m_speed;
    Vector3 m_startPosition;
    Vector3 m_endPosition;
    Vector3 m_idlePosition;
    Vector3 m_goal;
    Vector3 m_distanceToHexapod;
    Vector3 m_gotoDirCenterPosition;
};

#endif /* HEXAPODE_LEG_H_ */
