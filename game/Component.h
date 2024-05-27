#pragma once
#include <SDL.h>
#include <glm.hpp>

// a mostly abstract class to represent different bits of modular functionality to add to Objects
class Component
{
public:
	Component(class Object* owner, unsigned updatePriority = 0);
	virtual ~Component();

	// Update this component by delta time - called by owning Object
	virtual void Update(float deltaTime);
	// Process input for this component (if needed) - called by owning Object
	virtual void ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse);

	int GetUpdateOrder() const { return mUpdatePriority; }
	class Object* GetOwner() const { return mOwner; }
	class Game* GetGame() const;

protected:
	// Object that this component is a part of
	class Object* mOwner;
	// Update order - larger priority will be updated sooner
	unsigned mUpdatePriority;
};

