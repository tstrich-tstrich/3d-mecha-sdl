#include "PhysicsComp.h"
#include "Object.h"

PhysicsComp::PhysicsComp(std::weak_ptr<class Object> owner, float mass)
	:Component(owner)
	,mMass(mass)
	,mAccel(glm::vec3(0,0,0))
	,mCurrVelocity(glm::vec3(0, 0, 0))
	,mPrevVelocity(glm::vec3(0, 0, 0))
	,mPrevPosition(owner.lock().get()->GetPosition())
{
}

void PhysicsComp::Update(float deltaTime)
{
	Object* owner = mOwner.lock().get();
	mPrevVelocity = mCurrVelocity;
	mCurrVelocity = (owner->GetPosition() - mPrevPosition) / deltaTime;
	mPrevPosition = owner->GetPosition();
	mCurrVelocity += mAccel * deltaTime;
	owner->SetPosition(owner->GetPosition() + .5f * deltaTime * (mCurrVelocity + mPrevVelocity));
}

void PhysicsComp::ApplyForce(glm::vec3 force)
{
	mAccel += force * (1 / mMass);
}
