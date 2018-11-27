#pragma once
#include "stdafx.h"
#include "Triangle.h"

struct QuadMesh
{
public:
	QuadMesh() {}
	QuadMesh(const Triangle &InTriangle1, const Triangle &InTriangle2)
	{
		Triangles[0] = InTriangle1;
		Triangles[1] = InTriangle2;
	}

public:
	Triangle Triangles[2];
};