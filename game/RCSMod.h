#pragma once
#include "MechModule.h"
class RCSMod : public MechModule
{
public:
	RCSMod(std::weak_ptr<class SystemsComp> ownerSys, float turnSpeed, bool isGyro, float resrcAmount)
		:MechModule(ownerSys)
		, mIsGyro(isGyro)
		, mResourceUseRate(resrcAmount)
		,mTurnSpeed(turnSpeed)
	{}

	float GetUseRate() const { return mResourceUseRate; }
	float GetTurnSpeed() const { return mTurnSpeed; }
	MechResource GetResourceType() const {
		if (mIsGyro)
		{
			return MechResource::Electricity;
		}
		else
		{
			return MechResource::Hydrogen;
		}
	}

protected:
	bool mIsGyro;
	float mResourceUseRate;
	float mTurnSpeed;
};

