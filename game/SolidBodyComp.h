#pragma once
#include "Component.h"
class SolidBodyComp : public Component
{
public:
	SolidBodyComp(std::weak_ptr<class Object> owner);

	void OnCollision(std::weak_ptr<class Object> other) override;
};

