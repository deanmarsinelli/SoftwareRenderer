/*
	Box.cpp
	Author: Dean Marsinelli
*/

#include "Box.h"
#include "Colors.h"

Box::Box(const Mat4x4& worldMatrix) :
	GameObject(worldMatrix)
{
	vBuffer = {
		{ Vector4F(-1.0f, -1.0f, -1.0f), Colors::White, TexCoord(0.0f, 1.0f) },
		{ Vector4F(-1.0f, +1.0f, -1.0f), Colors::Black, TexCoord(0.0f, 0.0f) },
		{ Vector4F(+1.0f, +1.0f, -1.0f), Colors::Red, TexCoord(1.0f, 0.0f) },
		{ Vector4F(+1.0f, -1.0f, -1.0f), Colors::Green, TexCoord(1.0f, 1.0f) },
		{ Vector4F(-1.0f, -1.0f, +1.0f), Colors::Blue, TexCoord(1.0f, 1.0f) },
		{ Vector4F(-1.0f, +1.0f, +1.0f), Colors::Yellow, TexCoord(1.0f, 0.0f) },
		{ Vector4F(+1.0f, +1.0f, +1.0f), Colors::Cyan, TexCoord(0.0f, 0.0f) },
		{ Vector4F(+1.0f, -1.0f, +1.0f), Colors::Magenta, TexCoord(0.0f, 1.0f) }
	};

	iBuffer = {
		// front face
		0, 1, 2,
		0, 2, 3,
		// back face
		4, 6, 5,
		4, 7, 6,
		// left face
		4, 5, 1,
		4, 1, 0,
		// right face
		3, 2, 6,
		3, 6, 7,
		// top face
		1, 5, 6,
		1, 6, 2,
		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	texture = Graphics::LoadTexture(L"..\\source\\crate.bmp");
	texWidth = 256;
	texHeight = 256;
}
