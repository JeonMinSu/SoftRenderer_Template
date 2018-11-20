#pragma once

#include "stdafx.h"
#include "Vector.h"

struct Vertex
{
public:

	Vector3 position;
	//Vector3 uv;
	ULONG color;

	Vertex(Vector3 v, ULONG c) : position(v), color(c) {}

};