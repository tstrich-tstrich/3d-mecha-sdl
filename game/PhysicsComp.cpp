#include "PhysicsComp.h"
#include "Object.h"
#include <numeric>

PhysicsComp::PhysicsComp(std::weak_ptr<class Object> owner, float mass)
	:Component(owner, 100)
	,mMass(mass)
	,mAccel(glm::vec3(0,0,0))
	,mCurrVelocity(glm::vec3(0, 0, 0))
	,mPrevVelocity(glm::vec3(0, 0, 0))
	,mCurrForce(glm::vec3(0, 0, 0))
	,mPrevPosition(owner.lock().get()->GetPosition())
{
}

void PhysicsComp::Update(float deltaTime)
{
	Object* owner = mOwner.lock().get();
	
	mCurrForce = glm::vec3(0, 0, 0);
	for (glm::vec3& force : mForcesBuffer)
	{
		mCurrForce += force;
	}

	mAccel += mCurrForce * (1 / mMass);
	mPrevVelocity = mCurrVelocity;
	mCurrVelocity = (owner->GetPosition() - mPrevPosition) / deltaTime;
	mPrevPosition = owner->GetPosition();
	mCurrVelocity += mAccel * deltaTime;
	owner->SetPosition(owner->GetPosition() + .5f * deltaTime * (mCurrVelocity + mPrevVelocity));

	mCurrForce = glm::vec3(0, 0, 0);
	mForcesBuffer.clear();
}

void PhysicsComp::ApplyForce(glm::vec3 force)
{
	mForcesBuffer.push_back(force);
}
