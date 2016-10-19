/*
	GameObject.cpp
	Author: Dean Marsinelli
*/

#include "GameObject.h"

GameObject::GameObject(const Mat4x4& worldMatrix)
{
	worldMat = worldMatrix;
	texture = nullptr;
	texWidth = 0;
	texHeight = 0;
}

void GameObject::SetVertexBuffer(const VertexBuffer& vertexBuffer)
{
	vBuffer = vertexBuffer;
}

void GameObject::SetIndexBuffer(const IndexBuffer& indexBuffer)
{
	iBuffer = indexBuffer;
}

void GameObject::Draw(Graphics* graphics)
{
	graphics->BindVertexBuffer(&vBuffer);
	graphics->BindIndexBuffer(&iBuffer);
	graphics->BindMatrix(&worldMat, WORLD);
	if (texture)
	{
		graphics->BindTexture(texture, texWidth, texHeight);
	}

	graphics->DrawIndexed();
}
