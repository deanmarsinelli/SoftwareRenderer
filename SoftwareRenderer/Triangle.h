#pragma once

#include "Vertex.h"

struct Triangle
{
	Vertex p0;
	Vertex p1;
	Vertex p2;
};


class Edge
{
public:
	Edge(int x0, int y0, float z0, const Vector4F& color0, int x1, int y1, float z1, const Vector4F& color1);

	Vector4F color0, color1;
	int x0, y0, x1, y1;
	float z0, z1;
};


class Span
{
public:
	Span(int x0, float z0, const Vector4F& color0, int x1, float z1, const Vector4F& color1);

	Vector4F color0, color1;
	int x0, x1;
	float z0, z1;
};
