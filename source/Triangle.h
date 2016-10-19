/*
	Triangle.h
	Author: Dean Marsinelli

	Triangle struct and edge/span classes for rasterizing
	triangles with color and texture.
*/

#pragma once

#include "Vertex.h"

struct Triangle
{
	Vertex p0;
	Vertex p1;
	Vertex p2;
};

class EdgeColor
{
public:
	EdgeColor(int x0, int y0, float z0, const Vector4F& color0, int x1, int y1, float z1, const Vector4F& color1);

	Vector4F color0, color1;
	int x0, y0, x1, y1;
	float z0, z1;
};

class EdgeTexture
{
public:
	EdgeTexture(int x0, int y0, float z0, const TexCoord& texCoord0, int x1, int y1, float z1, const TexCoord& texCoord1);

	TexCoord texCoord0, texCoord1;
	int x0, y0, x1, y1;
	float z0, z1;
};

class SpanColor
{
public:
	SpanColor(int x0, float z0, const Vector4F& color0, int x1, float z1, const Vector4F& color1);

	Vector4F color0, color1;
	int x0, x1;
	float z0, z1;
};

class SpanTexture
{
public:
	SpanTexture(int x0, float z0, const TexCoord& texCoord0, int x1, float z1, const TexCoord& texCoord1);

	TexCoord texCoord0, texCoord1;
	int x0, x1;
	float z0, z1;
};
