#pragma once
#include "Object.h"
class Player : public Object
{
public:
	Player();

protected:
	void UniqueUpdate(float deltaTime);
	void UniqueInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse);
};

