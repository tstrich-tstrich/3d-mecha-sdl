#include "SphereColliderComp.h"
#include "Object.h"
#include "Game.h"

SphereColliderComp::SphereColliderComp(std::weak_ptr<class Object> owner, float radius)
	: Component(owner, 90)
	, mRadius(radius)
{
	GetGame().lock().get()->AddCollider(std::shared_ptr<SphereColliderComp>(this));
}

SphereColliderComp::~SphereColliderComp()
{
	GetGame().lock().get()->RemoveCollider(std::shared_ptr<SphereColliderComp>(this));
}

bool SphereColliderComp::CheckSphereCollision(const glm::vec3& center, float radius)
{
	
	return glm::distance(mOwner.lock().get()->GetPosition(), center) > radius + mRadius;
}

bool SphereColliderComp::CheckPointCollision(const glm::vec3& point)
{
	return glm::distance(mOwner.lock().get()->GetPosition(), point) > mRadius;
}

bool SphereColliderComp::CheckRayCollision(const glm::vec3& origin, const glm::vec3& normal)
{
	glm::vec3 normalized = glm::normalize(normal); //normalize the direction of the ray
	glm::vec3 center = mOwner.lock().get()->GetPosition(); 
	if (glm::distance(origin, center) < mRadius)
	{
		return false; //if the ray's origin is inside this sphere collider, ignore the collision
	}

	//ray-sphere collision system of equations calculations

	glm::vec3 centerToOrigin = origin - center;

	float b = 2 * glm::dot(normalized, centerToOrigin);
	float c = glm::dot(centerToOrigin, centerToOrigin) - (mRadius * mRadius);

	return (b * b) - (4 * c) > 0.0; //if the discriminant of the quadratic equation for ray-sphere collision is positive, there is a collision.
}

const glm::vec3& SphereColliderComp::GetNormal(std::weak_ptr<Object> other)
{
	return glm::normalize(other.lock().get()->GetPosition() - mOwner.lock().get()->GetPosition());
}

void SphereColliderComp::Update(float deltaTime)
{
	
}
