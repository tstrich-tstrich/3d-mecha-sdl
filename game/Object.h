#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <SDL.h>
#include <vector>
#include "Component.h"

//a mostly abstract class that represents any possible object, player, obstacle, enemy, etc in the game. In-game objects will be an instance of a subclass of this, rather than a pure Object instance
class Object
{
public:
	Object(class Game* game);
	virtual ~Object();

	// Update function called from Game
	void Update(float deltaTime);
	// ProcessInput function called from Game
	void ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse);

	//getters and setters
	const glm::vec3& GetPosition() const { return mPosition; }
	void SetPosition(const glm::vec3& pos) { mPosition = pos; }

	glm::vec3 GetForwardVec();
	glm::vec3 GetUpVec();

	const glm::quat& GetRotation() const { return mRotation; }
	void SetPosition(const glm::quat& rot) { mRotation = rot; }

	void AddComponent(class Component* comp);
	// Returns component of type T, or null if doesn't exist
	template <typename T>
	T* GetComponent() const
	{
		for (auto& comp : mComponents)
		{
			T* foundComp = dynamic_cast<T*>(comp);
			if (foundComp != nullptr)
			{
				return foundComp;
			}
		}

		return nullptr;
	}

	class Game* GetGame() { return mGame; }
	
protected:
	glm::vec3 mPosition;
	glm::quat mRotation;
	class Game* mGame;
	std::vector<Component> mComponents;
	
};

