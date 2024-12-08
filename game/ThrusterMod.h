#pragma once
#include "MechModule.h"
class ThrusterMod : public MechModule
{
public:
	ThrusterMod(std::weak_ptr<class SystemsComp> ownerSys, glm::vec3 relativeThrustDir, float force, float hydroUse, float oxiRatio);

	void DoBurn(float percentThrottle);

	const glm::vec3 GetMaxBurnVector() const { return glm::normalize(mRelativeThrustDirection) * mForce; }

protected:
	glm::vec3 mRelativeThrustDirection;
	float mForce;

	float mFuelConsumption;
	float mOxidizerRatio;
};

