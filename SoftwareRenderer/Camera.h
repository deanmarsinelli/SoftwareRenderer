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
	Vector3F GetPosition();
	Vector3F GetDirection();
	Vector3F GetYawPitchRoll();

	void Update(float dt);
	void Draw(Graphics* graphics);
};
