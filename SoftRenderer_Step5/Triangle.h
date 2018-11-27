#pragma once

#include "stdafx.h"
#include "Vertex.h"

struct Triangle
{
public:
	Triangle() {}
	Triangle(Vertex v1, Vertex v2, Vertex v3)
	{
		vt[0] = v1;
		vt[1] = v2;
		vt[2] = v3;
		CaleTriangle();
	}

	void CaleTriangle()
	{
		for (int i = 0; i < 3; i++)
		{
			if (vt[i].position.X < minPos.X) minPos.X = vt[i].position.X;
			if (vt[i].position.Y < minPos.Y) minPos.Y = vt[i].position.Y;

			if (vt[i].position.X > maxPos.X) minPos.X = vt[i].position.X;
			if (vt[i].position.Y > maxPos.Y) minPos.Y = vt[i].position.Y;
		}

		u = vt[1].position - vt[0].position;
		v = vt[2].position - vt[0].position;

		dotUU = Vector3::Dot(u, u);
		dotUV = Vector3::Dot(u, v);
		dotVV = Vector3::Dot(v, v);
		invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

		minPt = minPos;
		maxPt = maxPos;

	}

	Vector2 GetBaryCentricCoordinate(const Vector3 &ptToCheck) const
	{
		Vector3 w = ptToCheck - vt[0].position;
		float dotUW = Vector3::Dot(u, w);
		float dotVW = Vector3::Dot(v, w);

		float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
		float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
		return Vector2(s, t);
	}

	ULONG GetInterpolatedColor(const Vector2 &baryValues) const 
	{

		BYTE RV1 = GetRValue(vt[0].color);
		BYTE RV2 = GetRValue(vt[1].color);
		BYTE RV3 = GetRValue(vt[2].color);

		BYTE GV1 = GetGValue(vt[0].color);
		BYTE GV2 = GetGValue(vt[1].color);
		BYTE GV3 = GetGValue(vt[2].color);

		BYTE BV1 = GetBValue(vt[0].color);
		BYTE BV2 = GetBValue(vt[1].color);
		BYTE BV3 = GetBValue(vt[2].color);

		BYTE FianlR = (BYTE)(RV1 * (1 - baryValues.X - baryValues.Y) + RV2 * baryValues.X + RV3 * baryValues.Y);
		BYTE FianlG = (BYTE)(GV1 * (1 - baryValues.X - baryValues.Y) + GV2 * baryValues.X + GV3 * baryValues.Y);
		BYTE FianlB = (BYTE)(BV1 * (1 - baryValues.X - baryValues.Y) + BV2 * baryValues.X + BV3 * baryValues.Y);

		return RGB32(FianlR, FianlG, FianlB);
	}

	Triangle GetTransformedTriangle(const Transform2D & newTransform) const
	{
		Triangle newTriangle = *this;
		for (int i = 0; i < 3; i++)
		{
			newTriangle.vt[i].position = newTriangle.vt[i].position * newTransform.TRSMatrix;
		}
		newTriangle.CaleTriangle();
		return newTriangle;
	}

public:
	Vertex vt[3];
	IntPoint minPt;
	IntPoint maxPt;

	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(INFINITY, INFINITY);

	float dotUU, dotUV, dotVV, invDenom;

	Vector3 u, v;

};