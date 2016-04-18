/*
	Camera.h
	Author: Dean Marsinelli

	Camera object used to create the view matrix
	every frame based on the camera's position and 
	look-at direction.
*/

#pragma once

#include "GameObject.h"
#include "Vector.h"
#include "Matrix.h"

class Camera : public GameObject
{
public:
	Camera(const Mat4x4& worldMatrix);

	void SetPosition(const Vector3F& position);
	void Rotate(const float yaw, const float pitch, const float roll);

	Vector3F GetPosition();
	Vector3F GetDirection();
	Vector3F GetRight();
	Vector3F GetUp();
	Vector3F GetYawPitchRoll();

	void Update(float dt);
	void Draw(Graphics* graphics);
};
