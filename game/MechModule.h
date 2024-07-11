#pragma once
#include <memory>
#include <vector>

#include "SystemsComp.h"

class MechModule
{
public:
	MechModule(class Object owner, class SystemsComp ownerSys);



	virtual int RequestResource(MechResource resource, int amount) { return -1; }
	virtual int ProvideResource(MechResource resource, int amount) { return -1; }

protected:
	std::weak_ptr<class Object> mOwner;
	std::weak_ptr<class SystemsComp> mMechSystem;

};

