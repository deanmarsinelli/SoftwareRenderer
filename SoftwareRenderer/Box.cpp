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
	/*vBuffer = {
		// Back face
		{ Vector4F(-1.0, -1.0, 1.0), Colors::Red },
		{Vector4F(1.0, -1.0, 1.0), Colors::Blue },
		{Vector4F(1.0, 1.0, 1.0), Colors::Green},
		{Vector4F(-1.0, 1.0, 1.0), Colors::Yellow},
		// Front face
		{Vector4F(-1.0, -1.0, -2.0), Colors::Red},
		{ Vector4F(-1.0, 1.0, -2.0), Colors::Blue },
		{ Vector4F(1.0, 1.0, -2.0), Colors::Green },
		{ Vector4F(1.0, -1.0, -2.0), Colors::Yellow },
		// Bottom face
		{Vector4F(-1.0, -1.0, -2.0), Colors::Red},
		{Vector4F(1.0, -1.0, -2.0), Colors::Red},
		{Vector4F(1.0, -1.0, 1.0), Colors::Red},
		{Vector4F(-1.0, -1.0, 1.0), Colors::Red},
		// Right face
		{Vector4F(1.0, -1.0, -2.0), Colors::Red},
		{Vector4F(1.0, 1.0, -2.0), Colors::Red},
		{Vector4F(1.0, 1.0, 1.0), Colors::Red},
		{Vector4F(1.0, -1.0, 1.0), Colors::Red},
		// Left face
		{Vector4F(-1.0, -1.0, -2.0), Colors::Red},
		{Vector4F(-1.0, -1.0, 1.0), Colors::Red},
		{Vector4F(-1.0, 1.0, 1.0), Colors::Red},
		{Vector4F(-1.0, 1.0, -2.0), Colors::Red},
		// front top face
		{Vector4F(-1.0, 1.0, 1.0), Colors::Red},
		{Vector4F(1.0, 1.0, 1.0), Colors::Red},
		{Vector4F(0.0, 2.0, 1.0), Colors::Red},
		// back top face
		{Vector4F(1.0, 1.0, -2.0), Colors::Red},
		{Vector4F(-1.0, 1.0, -2.0), Colors::Red},
		{Vector4F(0.0, 2.0, -2.0), Colors::Red}
	};

	iBuffer = {
		0, 1, 2, 0, 2, 3,    // Front face
		4, 5, 6, 4, 6, 7,    // Back face
		8, 9, 10, 8, 10, 11,  // Bottom face
		12, 13, 14, 12, 14, 15, // Right face
		16, 17, 18, 16, 18, 19,  // Left face
		20, 21, 22, // front top
		23, 24, 25
	};*/
}

void Box::Update(float dt)
{

}

