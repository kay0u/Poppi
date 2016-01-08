
#include "Math/Vector3.h"

const Vector3 Vector3::zero = Vector3(0,0,0);
const Vector3 Vector3::up = Vector3(0,0,0);
const Vector3 Vector3::down = Vector3(0,-1,0);
const Vector3 Vector3::left = Vector3(0,-1,0);
const Vector3 Vector3::right = Vector3(0,1,0);
const Vector3 Vector3::forward = Vector3(0,0,1);
const Vector3 Vector3::backward = Vector3(0,0,-1);

Vector3::Vector3():
	x(0),
	y(0),
	z(0)
{

}

Vector3::Vector3(float x, float y, float z):
	x(x),
	y(y),
	z(z)
{

}

Vector3::~Vector3()
{

}

float Vector3::magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::normalized()
{
	return (*this) / magnitude();
}

double Vector3::Distance(Vector3 v1, Vector3 v2)
{
   return sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v1.y));
}

Vector3 Vector3::operator+(const Vector3& v2)
{
	return Vector3(x + v2.x , y + v2.y, z + v2.z);
}

Vector3 Vector3::operator+(const float f)
{
	return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator-(const Vector3& v2)
{
	return Vector3(x - v2.x , y - v2.y, z - v2.z);
}


Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(float f)
{
	return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator*(const Vector3& v2)
{
	return Vector3(x * v2.x , y * v2.y, z * v2.z);
}

Vector3 Vector3::operator*(float f)
{
	return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(const Vector3& v2)
{
	return Vector3(x / v2.x , y / v2.y, z / v2.z);
}

Vector3 Vector3::operator/( float f)
{
	return Vector3(x / f, y / f, z / f);
}

bool Vector3::operator == (const Vector3 &v) const
{
    return ( (v.x == x) && (v.y == y) && (v.z == z));
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}
