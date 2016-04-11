/*
	Box.cpp
	Author: Dean Marsinelli
*/

#include "Box.h"
#include "Colors.h"

Box::Box(const Mat4x4& worldMatrix) :
	GameObject(worldMatrix)
{
	vBuffer.push_back({ Vector4F(-1.0f, -1.0f, -1.0f), Colors::White });
	vBuffer.push_back({ Vector4F(-1.0f, +1.0f, -1.0f), Colors::Black });
	vBuffer.push_back({ Vector4F(+1.0f, +1.0f, -1.0f), Colors::Red });
	vBuffer.push_back({ Vector4F(+1.0f, -1.0f, -1.0f), Colors::Green });
	vBuffer.push_back({ Vector4F(-1.0f, -1.0f, +1.0f), Colors::Blue });
	vBuffer.push_back({ Vector4F(-1.0f, +1.0f, +1.0f), Colors::Yellow });
	vBuffer.push_back({ Vector4F(+1.0f, +1.0f, +1.0f), Colors::Cyan });
	vBuffer.push_back({ Vector4F(+1.0f, -1.0f, +1.0f), Colors::Magenta });

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
}
