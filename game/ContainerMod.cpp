#include "ContainerMod.h"

ContainerMod::ContainerMod(std::weak_ptr<class SystemsComp> ownerSys, MechResource type, float maxStore)
: MechModule(ownerSys)
, mType(type)
, mMaxStorage(maxStore)
, mCurrentStorage(maxStore)
{
}

bool ContainerMod::RequestResource(MechResource resource, float amount)
{
	if (resource == mType && amount <= mCurrentStorage)
	{
		mCurrentStorage -= amount;
		return true;
	}
	else
	{
		return false;
	}
}

float ContainerMod::GetPercentFull() const
{
	return mCurrentStorage / mMaxStorage;
}
