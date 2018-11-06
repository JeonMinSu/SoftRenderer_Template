#pragma once
#include "stdafx.h"

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;

	Matrix2() : _11(1), _12(1), _21(1), _22(1) {}
	Matrix2(float In11, float In12, float In21, float In22) :
		_11(In11), _12(In12), _21(In21), _22(In22) {}

public:
	void SetIndentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	}

	void SetScale(float InX, float InY) 
	{
		SetIndentity();
		_11 = InX;
		_22 = InY;
	}

	void SetRotation(float degree) 
	{
		/*
		회전 행렬 공식
		Cos(th), -Sin(th)
		Sin(th), Cos(th)
		*/
		float radian = Deg2Rad(degree);

		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}
	void Transpose() 
	{
		/*
		회전 역행력
		Cos(th), Sin(th)
		-Sin(th),Cos(th)
		*/
		float temp = _12;
		_12 = _21;
		_21 = temp;
	}


	Matrix2 Matrix2::operator *(const Matrix2 & mat) const;
};