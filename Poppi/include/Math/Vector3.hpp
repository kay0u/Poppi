#pragma once

#ifdef __cplusplus
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

	static Vector3 up()
	{
		return Vector3(0,1,0);
	}

	static Vector3 down()
	{
		return Vector3(0,-1,0);
	}

	static Vector3 left()
	{
		return Vector3(-1,0,0);
	}

	static Vector3 right()
	{
		return Vector3(1,0,0);
	}

	static Vector3 forward()
	{
		return Vector3(0,0,1);
	}

	static Vector3 backward()
	{
		return Vector3(0,0,-1);
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

	float x;
	float y;
	float z;

};
#endif
