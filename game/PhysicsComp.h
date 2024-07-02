#pragma once
#include "Component.h"
class PhysicsComp : public Component
{
public:
	PhysicsComp(std::weak_ptr<class Object> owner, float mass = 1);

	void Update(float deltaTime) override;

	void ApplyForce(glm::vec3 force);

private:
	float mMass;
	glm::vec3 mAccel;
	glm::vec3 mCurrVelocity;
	glm::vec3 mPrevVelocity;
	glm::vec3 mPrevPosition;
};

