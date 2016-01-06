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
	Vector3():
		x(0),
		y(0),
		z(0)
	{

	}

	Vector3(float x, float y, float z):
		x(x),
		y(y),
		z(z)
	{

	}

	~Vector3();

	static const Vector3 zero;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 forward;
	static const Vector3 backward;

	float magnitude()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vector3 normalized()
	{
		return (*this) / magnitude();
	}

	static double Distance(Vector3 v1, Vector3 v2)
	{
	   return sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v1.y));
	}

    friend Vector3 operator+(const Vector3& v1, const Vector3& v2)
    {
    	return Vector3(v1.x + v2.x , v1.y + v2.y, v1.z + v2.z);
    }

    friend Vector3 operator+(const Vector3& v1, float f)
    {
    	return Vector3(v1.x + f, v1.y + f, v1.z + f);
    }

    friend Vector3 operator-(const Vector3& v1, const Vector3& v2)
    {
    	return Vector3(v1.x - v2.x , v1.y - v2.y, v1.z - v2.z);
    }

    friend Vector3 operator-(const Vector3& v1)
    {
    	return Vector3(-v1.x, -v1.y, -v1.z);
    }

    friend Vector3 operator-(const Vector3& v1, float f)
    {
    	return Vector3(v1.x - f, v1.y - f, v1.z - f);
    }

    friend Vector3 operator*(const Vector3& v1, const Vector3& v2)
    {
    	return Vector3(v1.x * v2.x , v1.y * v2.y, v1.z * v2.z);
    }

    friend Vector3 operator*(const Vector3& v1, float f)
    {
    	return Vector3(v1.x * f, v1.y * f, v1.z * f);
    }

    friend Vector3 operator/(const Vector3& v1, const Vector3& v2)
    {
    	return Vector3(v1.x / v2.x , v1.y / v2.y, v1.z / v2.z);
    }

    friend Vector3 operator/(const Vector3& v1, float f)
    {
    	return Vector3(v1.x / f, v1.y / f, v1.z / f);
    }

    inline bool operator == (const Vector3 &v) const
    {
        return ( (v.x == x) && (v.y == y) && (v.z == z));
    }

    Vector3& operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& operator*=(const Vector3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector3& operator/=(const Vector3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

	float x;
	float y;
	float z;

};

const Vector3 Vector3::zero = Vector3(0,0,0);
const Vector3 Vector3::up = Vector3(0,0,0);
const Vector3 Vector3::down = Vector3(0,-1,0);
const Vector3 Vector3::left = Vector3(0,-1,0);
const Vector3 Vector3::right = Vector3(0,1,0);
const Vector3 Vector3::forward = Vector3(0,0,1);
const Vector3 Vector3::backward = Vector3(0,0,-1);
#endif
