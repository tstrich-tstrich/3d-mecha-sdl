#pragma once
#include <SDL.h>
#include <glm.hpp>
#include <memory>

// a mostly abstract class to represent different bits of modular functionality to add to Objects
class Component
{
public:
	Component(std::weak_ptr<class Object> owner, unsigned updatePriority = 0);
	virtual ~Component();

	// Update this component by delta time - called by owning Object
	virtual void Update(float deltaTime);
	// Process input for this component (if needed) - called by owning Object
	virtual void ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse);

	int GetUpdateOrder() const { return mUpdatePriority; }
	std::weak_ptr<class Object> GetOwner() const { return mOwner; }
	class std::weak_ptr<class Game> GetGame() const;

protected:
	// Object that this component is a part of
	std::weak_ptr<class Object> mOwner;
	// Update order - larger priority will be updated sooner
	unsigned mUpdatePriority;
};

