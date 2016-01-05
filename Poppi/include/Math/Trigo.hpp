#pragma once


#ifdef __cplusplus
class Trigo
{
public:
	Trigo();
	~Trigo();

	static const float Deg2Rad;
	static const float Rad2Deg;
};

float Trigo::Deg2Rad = 0.0174533f;
float Trigo::Rad2Deg = 57.2958f;

#endif
