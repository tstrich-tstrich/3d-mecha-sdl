#include "ThrusterMod.h"
#include "Object.h"
#include "PhysicsComp.h"
#include "SystemsComp.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/quaternion.hpp>

ThrusterMod::ThrusterMod(std::weak_ptr<class SystemsComp> ownerSys, glm::vec3 relativeThrustDir, float force, float hydroUse, float oxiRatio)
	:MechModule(ownerSys)
	,mRelativeThrustDirection(relativeThrustDir)
	,mForce(force)
	,mFuelConsumption(hydroUse)
	,mOxidizerRatio(oxiRatio)
{
}

void ThrusterMod::DoBurn(float percentThrottle)
{
	SystemsComp* system = mMechSystem.lock().get();

	bool fuelUse = system->UseResource(std::shared_ptr<MechModule>(this), MechResource::Hydrogen, mFuelConsumption * percentThrottle);
	if (!fuelUse)
	{
		return;
	}
	bool oxidizerUse = system->UseResource(std::shared_ptr<MechModule>(this), MechResource::Oxidizer, mFuelConsumption * percentThrottle * mOxidizerRatio);
	if (!oxidizerUse)
	{
		return;
	}
	
	Object* owner = mOwner.lock().get();

	glm::vec3 force = glm::rotate(owner->GetRotation(), mRelativeThrustDirection) * mForce * percentThrottle;
	owner->GetComponent<PhysicsComp>().lock().get()->ApplyForce(force);
}
