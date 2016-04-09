#pragma once

#include "GameObject.h"

class Box : public GameObject
{
public:
	Box(const Mat4x4& worldMatrix);

	void Update(float dt);
};
