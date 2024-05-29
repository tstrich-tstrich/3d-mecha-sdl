#include "Component.h"

Component::Component(Object* owner, unsigned updatePriority)
{
}

Component::~Component()
{
}

void Component::Update(float deltaTime)
{
}

void Component::ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse)
{
}

std::weak_ptr<class Game> Component::GetGame() const
{
	return mOwner.lock().get()->GetGame();
}
