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
#include "../Math/Vector3.h"
#include "../Math/Trigo.h"

#define GAMMA_CENTER_OFFSET 150
#define GAMMA_MINIMUM 50
#define GAMMA_MAXIMUM 250
#define ALPHA_CENTER_OFFSET 60
#define ALPHA_MINIMUM 50
#define ALPHA_MAXIMUM 190
#define BETA_CENTER_OFFSET 150
#define BETA_MINIMUM 50
#define BETA_MAXIMUM 250

enum LegPosition {
	Idle,
	Start,
	End
};

class Leg {
public:
	Leg(int startAxId);
	virtual ~Leg();
	void initRelativePosition(Vector3 dist, float angle);
	Vector3 hexapodSpaceToLocalSpace(Vector3 pos);
	void setDirection(Vector3 dir);
	void stop();
	bool hasReachedGoal();
	Vector3 processIK(Vector3 pos);
	void goToIK(Vector3 pos);
	void goTo(LegPosition pos);
	void goToAngleAx(Vector3 angles);
	void goToAngleIK(Vector3 angles);
private:

	//Servos
	Servo m_gamma;						//Servo entre le corps et le coxa
	Servo m_alpha;						//Servo entre le coxa et le femur
	Servo m_beta;						//Servo entre le tibia et le femur

	//Geometry
	const float m_tibiaLength;			//Distance entre le moteur trois et la pointe de la patte
	const float m_femurLength;			//Distance entre les moteurs deux et trois
	const float m_coxaLength;			//Distance entre les deux premiers moteurs
	float m_angleToHexapod;				//Différence d'angle entre le repère de la patte et le repère de l'hexapode
    Vector3 m_distanceToHexapod;		//Distance entre l'origine du repère de la patte et l'origine du repère de l'hexapode

	//Kinematic
	float m_speed;						//Vitesse de déplacement
    Vector3 m_startPosition;			//Position au début du mouvement
    Vector3 m_endPosition;				//Position à la fin du mouvement
    Vector3 m_idlePosition;				//Position en Idle (patte en l'air)
    Vector3 m_goal;						//Position à atteindre par la pointe  de la patte
    Vector3 m_gotoDirCenterPosition;	//Le point situé au centre du segment effectué par la pointe de la patte lors du déplacement. start et end son position en fonction de ce point.
};

#endif /* HEXAPODE_LEG_H_ */
