#pragma once
#include "Component.h"
#include <vector>
class PhysicsComp : public Component
{
public:
	PhysicsComp(std::weak_ptr<class Object> owner, float mass = 1);

	void Update(float deltaTime) override;

	void ApplyForce(glm::vec3 force);

	void SetMass(float mass) { mMass = mass; }

private:
	float mMass;
	glm::vec3 mAccel;
	glm::vec3 mCurrVelocity;
	glm::vec3 mPrevVelocity;
	glm::vec3 mPrevPosition;
	glm::vec3 mCurrForce;

	std::vector<glm::vec3> mForcesBuffer;
};

