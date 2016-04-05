#pragma once

#include <vector>

#include <d3d9.h>
#include "Vector.h"

struct Vertex
{
	Vector3F position;
	Vector4F color;
};

typedef std::vector<Vertex> VertexBuffer;

typedef unsigned long Index;
typedef std::vector<Index> IndexBuffer;
