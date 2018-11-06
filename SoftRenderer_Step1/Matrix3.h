#pragma once
#include "stdafx.h"

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3() : _11(1), _12(1), _13(1),
				_21(1), _22(1), _23(1),
				_31(1), _32(1), _33(1) {}

	Matrix3(float In11, float In12, float In13, float In21, float In22, float In23, float In31, float In32, float In33) :
		_11(In11), _12(In12), _13(In13),
		_21(In21), _22(In22), _23(In23),
		_31(In31), _32(In32), _33(In33) {}


	void SetIndentity()
	{
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
		_31 = 0.0f; _32 = 0.0f; _31 = 1.0f;
	}

	void SetScale(float InX, float InY, float InZ)
	{
		SetIndentity();
		_11 = InX;
		_22 = InY;
		_33 = InZ;
	}

	void SetRotation(float degree)
	{
		float radian = Deg2Rad(degree);

		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = -_12;
		_22 = _11;
	}

	void SetTranslation(float InX, float InY)
	{
		SetIndentity();
		_13 = InX;
		_23 = InY;
	}

	void Transpose()
	{
		float temp = _12;

		_12 = _21;
		_21 = temp;

		temp = _13;
		_31 = temp;
	}
	Matrix3 Matrix3::operator *(const Matrix3 & mat) const;

};