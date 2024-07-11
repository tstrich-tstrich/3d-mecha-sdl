#pragma once
#include "Component.h"

enum MechResource
{
	Electricity,
	Ammo,
	Fuel,
	Oxidizer,
	DataFeed
};

class SystemsComp : public Component
{
	SystemsComp(std::weak_ptr<class Object> owner);



};

