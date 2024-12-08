#pragma once
#include "MechModule.h"
class PilotSeat : public MechModule
{
public:
	static float 
	PilotSeat(std::weak_ptr<class SystemsComp> ownerSys);

	bool PilotIsAlive();
protected:

};

