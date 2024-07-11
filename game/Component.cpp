#include "Component.h"
#include "Object.h"

Component::Component(std::weak_ptr<class Object> owner, unsigned updatePriority)
	:mUpdatePriority(updatePriority)
	,mOwner(owner)
{
	mOwner.lock().get()->AddComponent(std::shared_ptr<Component>(this));
}

std::weak_ptr<class Game> Component::GetGame() const
{
	return mOwner.lock().get()->GetGame();
}
