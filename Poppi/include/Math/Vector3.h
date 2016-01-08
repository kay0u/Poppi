/*
 * Vector3.hpp
 *
 *  Created on: 5 janv. 2016
 *      Author: Vincent
 */

#ifndef MATH_VECTOR3_H_
#define MATH_VECTOR3_H_

#include <math.h>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	float magnitude();
	Vector3 normalized();
	static double Distance(Vector3 v1, Vector3 v2);
	Vector3 operator+(const Vector3& v2);
	Vector3 operator+(const float f);
	Vector3 operator-(const Vector3& v2);
	Vector3 operator-();
	Vector3 operator-(float f);
	Vector3 operator*( const Vector3& v2);
	Vector3 operator*(float f);
	Vector3 operator/(const Vector3& v2);
	Vector3 operator/(float f);
	bool operator == (const Vector3 &v) const;
	Vector3& operator-=(const Vector3& v);
	Vector3& operator+=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator/=(const Vector3& v);

	static const Vector3 zero;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 forward;
	static const Vector3 backward;


	float x;
	float y;
	float z;

};
#endif
