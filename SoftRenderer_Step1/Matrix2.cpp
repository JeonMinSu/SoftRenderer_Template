#include "stdafx.h"
#include "Matrix2.h"

Matrix2 Matrix2::operator *(const Matrix2 & mat) const 
{
	Matrix2 result;

	result._11 = _11 * mat._11 + _12 * mat._21;
	result._12 = _11 * mat._12 + _12 * mat._22;
	result._21 = _21 * mat._11 + _22 * mat._21;
	result._22 = _21 * mat._12 + _22 * mat._22;
	
	return result;

};
