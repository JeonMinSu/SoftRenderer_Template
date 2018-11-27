#pragma once

#include "stdafx.h"
#include "Triangle.h"

struct Mesh
{
public:
	Mesh() : Triangles(NULL) {}
	Mesh(Triangle *InTriangles) : Triangles(InTriangles)
	{}
public:
	Triangle* Triangles;
};