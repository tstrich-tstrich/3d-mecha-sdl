#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Component.h"

//a class that represents any possible object, player, obstacle, enemy, etc in the game. In-game objects will mostly be an instance of a subclass of this, rather than a pure Object instance
class Object
{
public:
	Object(std::weak_ptr<class Game> game);

	// Update function called from Game
	void Update(float deltaTime);
	// ProcessInput function called from Game
	void ProcessInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse);

	//send collision info all components
	void RegisterCollision(std::weak_ptr<Object> other);

	//getters and setters
	const glm::vec3& GetPosition() const { return mPosition; }
	void SetPosition(const glm::vec3& pos) { mPosition = pos; }

	glm::vec3 GetForwardVec() const;
	glm::vec3 GetUpVec() const;

	const glm::quat& GetRotation() const { return mRotation; }
	void SetRotation(const glm::quat& rot) { mRotation = rot; }

	void AddComponent(std::shared_ptr<class Component> comp);
	// Returns component of type T, or eampty weak_ptr if doesn't exist
	template <typename T>
	std::weak_ptr<T> GetComponent() const
	{
		for (auto& comp : mComponents)
		{
			std::shared_ptr<T> foundComp = std::dynamic_pointer_cast<T>(comp);
			if (foundComp != nullptr)
			{
				return std::weak_ptr<T>(foundComp);
			}

		}

		return std::weak_ptr<T>();
	}

	class std::weak_ptr<class Game> GetGame() { return mGame; }
	
protected:
	glm::vec3 mPosition;
	glm::quat mRotation;
	std::weak_ptr<class Game> mGame;

	//we don't need component deletion and creation buffers because an object's component vector should only be modified on object creation
	std::vector<std::shared_ptr<Component>> mComponents;
	
	//overrided by subclasses for any unique subclass behavior
	virtual void UniqueUpdate(float deltaTime){}
	virtual void UniqueInput(const Uint8* keyState, Uint32 mouseButtons, const glm::vec2& relativeMouse){}
};

