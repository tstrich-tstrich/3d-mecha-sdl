#pragma once
#include "Component.h"
#include <map>
#include <vector>

enum MechResource
{
	Electricity,
	Ammo,
	Hydrogen,
	Oxidizer,
	DataFeed
};

class SystemsComp : public Component
{
public:
	SystemsComp(std::weak_ptr<class Object> owner);

	void LoadDefaultMechConfig();

	void Move(const glm::vec3& direction, float throttle);
	void RotateTowardsTarget();
	bool FireWeapon();
	void CycleWeapons();

	bool UseResource(std::shared_ptr<class MechModule> destModule, MechResource resource, float amount);

	void OnCollision(std::weak_ptr<class Object> other) override;
	void Update(float deltaTime) override;

protected:
	std::vector<std::shared_ptr<class MechModule>> mModules;
	std::vector<std::shared_ptr<class ThrusterMod>> mMainThrusters;
	std::vector<std::shared_ptr<class RCSMod>> mReactionControls;

	glm::vec3 mTargetForward;
	float mRotationSpeed;

	std::map<std::shared_ptr<class MechModule>, std::map<std::shared_ptr<class MechModule>, bool>> mConnectionMatrix;
};

