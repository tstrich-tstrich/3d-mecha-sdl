#include "PhysicsComp.h"

PhysicsComp::PhysicsComp(std::weak_ptr<class Object> owner, float mass)
	:Component(owner)
	,mMass(mass)
{
}

void PhysicsComp::Update(float deltaTime)
{

}

void PhysicsComp::ApplyForce(glm::vec3 force)
{
	mAccel += force * (1 / mMass);
}
