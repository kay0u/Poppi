/*
 * Trigo.hpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#ifndef MATH_TRIGO_H_
#define MATH_TRIGO_H_

class Trigo
{
public:
	Trigo();
	~Trigo();

	static const float Deg2Rad;
	static const float Rad2Deg;
	static const float Pi;
};

const float Trigo::Deg2Rad = 0.0174533f;
const float Trigo::Rad2Deg = 57.2958f;
const float  Trigo::Pi = 3.14159265358979323846;

#endif
