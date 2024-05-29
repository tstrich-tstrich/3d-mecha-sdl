#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Component.h"

//a mostly abstract class that represents any possible object, player, obstacle, enemy, etc in the game. In-game objects will mostly be an instance of a subclass of this, rather than a pure Object instance
class Object
{
public:
	Object(std::weak_ptr<class Game> game);
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

	void AddComponent(std::shared_ptr<class Component> comp);
	// Returns component of type T, or null if doesn't exist
	template <typename T>
	std::weak_ptr<T> GetComponent() const
	{
		for (auto& comp : mComponents)
		{
			std::weak_ptr<T> foundComp = dynamic_cast<std::shared_ptr<T>>(comp);
			if (foundComp != nullptr)
			{
				return foundComp;
			}
		}

		return nullptr;
	}

	class std::weak_ptr<class Game> GetGame() { return mGame; }
	
protected:
	glm::vec3 mPosition;
	glm::quat mRotation;
	std::weak_ptr<class Game> mGame;
	std::vector<std::shared_ptr<Component>> mComponents;
	
	//overrided by subclasses for any unique subclass behavior
	virtual void UniqueUpdate(float deltaTime){}
	virtual void UniqueInput(float deltaTime){}
};

