#pragma once

#include <vector>

#include <d3d9.h>
#include "Vector.h"

struct Vertex
{
	Vector4F position;  // just leave w as 1
	Vector4F color;
	TexCoord texCoord;
};

typedef std::vector<Vertex> VertexBuffer;

typedef unsigned long Index;
typedef std::vector<Index> IndexBuffer;
typedef Vec2<int> TexCoord;
