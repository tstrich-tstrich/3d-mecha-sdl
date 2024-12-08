#pragma once
#include <memory>
#include <vector>

#include "SystemsComp.h"

//abstract class representing a part of a mech, like an engine or weapon etc etc. these are managed by one systemscomp on each mech game object
class MechModule
{
public:
	MechModule(std::weak_ptr<class SystemsComp> ownerSys)
		:mMechSystem(ownerSys)
		,mOwner(ownerSys.lock().get()->GetOwner())
	{
	}

	bool mIsActive = true;
	bool mIsDamaged = false;

	virtual bool RequestResource(MechResource resource, float amount) { return false; }

protected:
	std::weak_ptr<class Object> mOwner;
	std::weak_ptr<class SystemsComp> mMechSystem;

	bool mCanTransferResources = false;
};

