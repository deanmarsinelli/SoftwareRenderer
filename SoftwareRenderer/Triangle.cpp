#include "Triangle.h"

Edge::Edge(int x0, int y0, float z0, const Vector4F& color0, int x1, int y1, float z1, const Vector4F& color1)
{
	if (y0 < y1) 
	{
		this->color0 = color0;
		this->x0 = x0;
		this->y0 = y0;
		this->z0 = z0;
		this->color1 = color1;
		this->x1 = x1;
		this->y1 = y1;
		this->z1 = z1;
	}
	else 
	{
		this->color0 = color1;
		this->x0 = x1;
		this->y0 = y1;
		this->z0 = z1;
		this->color1 = color0;
		this->x1 = x0;
		this->y1 = y0;
		this->z1 = z0;
	}
}

Span::Span(int x0, float z0, const Vector4F& color0, int x1, float z1, const Vector4F& color1)
{
	if (x0 < x1)
	{
		this->color0 = color0;
		this->x0 = x0;
		this->z0 = z0;
		this->color1 = color1;
		this->x1 = x1;
		this->z1 = z1;
	}
	else
	{
		this->color0 = color1;
		this->x0 = x1;
		this->z0 = z1;
		this->color1 = color0;
		this->x1 = x0;
		this->z1 = z0;
	}
}
