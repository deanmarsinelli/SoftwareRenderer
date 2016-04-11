/*
	Camera.cpp
	Author: Dean Marsinelli
*/

#include "Camera.h"

Camera::Camera(const Mat4x4& worldMatrix) :
	GameObject(worldMatrix)
{
	worldMat.SetPosition(Vector3F(0.0f, 0.0f, -10.0f));
}

void Camera::Update(float dt)
{ 
}

void Camera::Draw(Graphics* graphics)
{ 
}

void Camera::SetPosition(const Vector3F& position)
{
	worldMat.SetPosition(position);
}

Vector3F Camera::GetPosition()
{
	return worldMat.GetPosition();
}

Vector3F Camera::GetDirection()
{
	return worldMat.GetDirection();
}

Vector3F Camera::GetYawPitchRoll()
{
	return worldMat.GetYawPitchRoll();
}
