#include "stdafx.h"
#include "Matrix3.h"

Matrix3 Matrix3::operator*(const Matrix3 & mat) const
{
	Matrix3 result;
	
	result._11 = _11 * mat._11 + _12 * mat._21 + _13 * mat._31;
	result._12 = _11 * mat._12 + _12 * mat._22 + _13 * mat._32;
	result._13 = _11 * mat._13 + _12 * mat._23 + _13 * mat._33;
											   
	result._21 = _21 * mat._11 + _22 * mat._21 + _23 * mat._31;
	result._22 = _21 * mat._12 + _22 * mat._22 + _23 * mat._32;
	result._23 = _21 * mat._13 + _22 * mat._23 + _23 * mat._33;
											   
	result._31 = _31 * mat._11 + _32 * mat._21 + _33 * mat._31;
	result._32 = _31 * mat._12 + _32 * mat._22 + _33 * mat._32;
	result._33 = _31 * mat._13 + _32 * mat._23 + _33 * mat._33;

	return result;

}
