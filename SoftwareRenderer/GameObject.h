/*
	GameObject.h
	Author: Dean Marsinelli

	Base class for all objects in the game. Contains
	a world matrix for position/rotation/scale, a
	vertex buffer, and index buffer. Subclasses can
	override the Update and Draw methods.
*/

#pragma once

#include "Graphics.h"
#include "Matrix.h"
#include "Vertex.h"

class GameObject
{
public:
	GameObject(const Mat4x4& worldMatrix);

	void SetVertexBuffer(const VertexBuffer& vertexBuffer);
	void SetIndexBuffer(const IndexBuffer& indexBuffer);

	virtual void Update(float dt) { }
	virtual void Draw(Graphics* graphics);

protected:
	Mat4x4 worldMat;
	VertexBuffer vBuffer;
	IndexBuffer iBuffer;
};
