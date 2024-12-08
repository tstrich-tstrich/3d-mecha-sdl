#pragma once
#include "MechModule.h"
class ContainerMod : public MechModule
{
public:
	ContainerMod(std::weak_ptr<class SystemsComp> ownerSys, MechResource type, float maxStore);

	bool RequestResource(MechResource resource, float amount);

	MechResource GetType() const { return mType; }

	float GetPercentFull() const;

protected:

	MechResource mType;
	float mMaxStorage;
	float mCurrentStorage;
};

