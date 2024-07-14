#pragma once
#include "Component.h"
class SphereColliderComp : public Component
{
public:
	SphereColliderComp(std::weak_ptr<class Object> owner, float radius);
	~SphereColliderComp();

	virtual bool CheckSphereCollision(const glm::vec3& center, float radius);
	virtual bool CheckPointCollision(const glm::vec3& point);
	virtual bool CheckRayCollision(const glm::vec3& origin, const glm::vec3& normal);

	virtual const glm::vec3& GetNormal(const glm::vec3& point);
	virtual float GetOverlap(std::weak_ptr<SphereColliderComp> other);

	virtual void Update(float deltaTime) override;

protected:
	float mRadius;
};

