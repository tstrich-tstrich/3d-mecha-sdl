#include "Component.h"
#include "Object.h"

Component::Component(std::weak_ptr<class Object> owner, unsigned updatePriority)
	:mUpdatePriority(updatePriority)
	,mOwner(owner)
{
	mOwner.lock().get()->AddComponent(std::shared_ptr<Component>(this));
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
