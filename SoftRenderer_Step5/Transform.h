#pragma once

#include "stdafx.h"
#include "Vector.h"

struct Transform2D
{
private:
	Matrix3 m_transformMatrix;
	Matrix3 m_rotationMatrix;
	Matrix3 m_scaleMatrix;

public:
	Vector2 Position;
	float Angle;
	Vector2 Scale;
	Matrix3 TRSMatrix;

public:
	Transform2D() : Angle(0) {}
	Transform2D(const Vector2 InPosition, float InAngle, const Vector2 InScale)
		: Position(InPosition), Angle(InAngle), Scale(InScale)
	{
		SetTRSMatrix();
	}

private:
	void SetTRSMatrix()
	{
		m_transformMatrix.SetTranslation(Position.X, Position.Y);
		m_rotationMatrix.SetRotation(Angle);
		m_rotationMatrix.SetScale(Scale.X, Scale.Y, 1);
		TRSMatrix = m_transformMatrix * m_rotationMatrix * m_rotationMatrix;
	}

};