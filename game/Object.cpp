#include "Object.h"

Object::Object(std::weak_ptr<class Game> game)
{
}

Object::~Object()
{
}

void Object::Update(float deltaTime)
{
}

void Object::ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse)
{
}

glm::vec3 Object::GetForwardVec()
{
	return glm::vec3();
}

glm::vec3 Object::GetUpVec()
{
	return glm::vec3();
}

void Object::AddComponent(std::shared_ptr<class Component> comp)
{
}
