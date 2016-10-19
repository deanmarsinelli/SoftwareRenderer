/*
	Triangle.cpp
	Author: Dean Marsinelli
*/

#include "Triangle.h"

EdgeColor::EdgeColor(int _x0, int _y0, float _z0, const Vector4F& _color0,
	int _x1, int _y1, float _z1, const Vector4F& _color1)
{
	if (_y0 < _y1)
	{
		color0 = _color0;
		x0 = _x0;
		y0 = _y0;
		z0 = _z0;
		color1 = _color1;
		x1 = _x1;
		y1 = _y1;
		z1 = _z1;
	}
	else 
	{
		color0 = _color1;
		x0 = _x1;
		y0 = _y1;
		z0 = _z1;
		color1 = _color0;
		x1 = _x0;
		y1 = _y0;
		z1 = _z0;
	}
}

EdgeTexture::EdgeTexture(int _x0, int _y0, float _z0, const TexCoord& _texCoord0, 
	int _x1, int _y1, float _z1, const TexCoord& _texCoord1)
{
	if (_y0 < _y1)
	{
		texCoord0 = _texCoord0;
		x0 = _x0;
		y0 = _y0;
		z0 = _z0;
		texCoord1 = _texCoord1;
		x1 = _x1;
		y1 = _y1;
		z1 = _z1;
	}
	else
	{
		texCoord0 = _texCoord1;
		x0 = _x1;
		y0 = _y1;
		z0 = _z1;
		texCoord1 = _texCoord0;
		x1 = _x0;
		y1 = _y0;
		z1 = _z0;
	}
}

SpanColor::SpanColor(int _x0, float _z0, const Vector4F& _color0, 
	int _x1, float _z1, const Vector4F& _color1)
{
	if (_x0 < _x1)
	{
		color0 = _color0;
		x0 = _x0;
		z0 = _z0;
		color1 = _color1;
		x1 = _x1;
		z1 = _z1;
	}
	else
	{
		color0 = _color1;
		x0 = _x1;
		z0 = _z1;
		color1 = _color0;
		x1 = _x0;
		z1 = _z0;
	}
}

SpanTexture::SpanTexture(int _x0, float _z0, const TexCoord& _texCoord0, 
	int _x1, float _z1, const TexCoord& _texCoord1)
{
	if (_x0 < _x1)
	{
		texCoord0 = _texCoord0;
		x0 = _x0;
		z0 = _z0;
		texCoord1 = _texCoord1;
		x1 = _x1;
		z1 = _z1;
	}
	else
	{
		texCoord0 = _texCoord1;
		x0 = _x1;
		z0 = _z1;
		texCoord1 = _texCoord0;
		x1 = _x0;
		z1 = _z0;
	}
}
