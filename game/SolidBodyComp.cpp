#include "SolidBodyComp.h"
#include "SphereColliderComp.h"
#include "Object.h"

SolidBodyComp::SolidBodyComp(std::weak_ptr<Object> owner)
	:Component(owner, 0)
{
}

void SolidBodyComp::OnCollision(std::weak_ptr<Object> other)
{
	std::weak_ptr<SolidBodyComp> otherBody = other.lock().get()->GetComponent<SolidBodyComp>();

	if (!otherBody.expired())
	{
		glm::vec3 otherPos = other.lock().get()->GetPosition();
		glm::vec3 oldPos = mOwner.lock().get()->GetPosition();
		std::weak_ptr<SphereColliderComp> ownerCol = mOwner.lock().get()->GetComponent<SphereColliderComp>();
		std::weak_ptr<SphereColliderComp> otherCol = other.lock().get()->GetComponent<SphereColliderComp>();
		glm::vec3 newPos = oldPos + (otherCol.lock().get()->GetNormal(oldPos) * ownerCol.lock().get()->GetOverlap(otherCol));
		mOwner.lock().get()->SetPosition(newPos);
	}
	
}
