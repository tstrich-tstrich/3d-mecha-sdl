#include "Object.h"
#include "Game.h"
#include <algorithm>
#include <gtx/quaternion.hpp>

Object::Object(std::weak_ptr<class Game> game)
	:mPosition(0,0,0)
	,mRotation(glm::vec3(0,0,0))
	,mGame(game)
{
	mGame.lock().get()->AddObject(std::shared_ptr<Object>(this));
}

Object::~Object()
{
}

void Object::Update(float deltaTime)
{
	//do any unique subclass behavior
	UniqueUpdate(deltaTime);

	//send update info to all components
	for (auto& comp : mComponents)
	{
		comp.get()->Update(deltaTime);
	}
}

void Object::ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse)
{
	//do any unique subclass input processing
	UniqueInput(keyState, mouseButtons, relativeMouse);

	//send input info to all components
	for (auto& comp : mComponents)
	{
		comp.get()->ProcessInput(keyState, mouseButtons, relativeMouse);
	}
}

glm::vec3 Object::GetForwardVec() const
{
	return glm::rotate(mRotation, glm::vec3(0.0,0.0,1.0));
}

glm::vec3 Object::GetUpVec() const
{
	return glm::rotate(mRotation, glm::vec3(0.0, 1.0, 0.0));
}

void Object::AddComponent(std::shared_ptr<class Component> comp)
{
	//should only be called on object creation, so can just directly add to components vector
	mComponents.push_back(comp);

	//sort by update priority
	std::sort(mComponents.begin(), mComponents.end(), [](std::shared_ptr<Component> comp1, std::shared_ptr<Component> comp2)
		{
			return comp1.get()->GetUpdateOrder() > comp2.get()->GetUpdateOrder();
		});
}
