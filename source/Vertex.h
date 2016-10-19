/*
	Vertex.h
	Author: Dean Marsinelli

	Basic Vertex struct and some types.
*/

#pragma once

#include <d3d9.h>
#include <vector>

#include "Vector.h"

typedef Vector2F TexCoord;
typedef unsigned long Index;

struct Vertex
{
	Vector4F position;  // just leave w as 1
	Vector4F color;
	TexCoord texCoord;
};

typedef std::vector<Vertex> VertexBuffer;
typedef std::vector<Index> IndexBuffer;
