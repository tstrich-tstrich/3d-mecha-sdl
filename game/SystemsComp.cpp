#include "SystemsComp.h"
#include "ThrusterMod.h"
#include "RCSMod.h"
#include "Object.h"

SystemsComp::SystemsComp(std::weak_ptr<class Object> owner)
    :Component(owner)
    ,mTargetForward(owner.lock().get()->GetForwardVec())
{
}

void SystemsComp::LoadDefaultMechConfig()
{

}

void SystemsComp::Move(const glm::vec3& direction, float throttle)
{
    ThrusterMod* thrustPtr;
    for (auto& thruster : mMainThrusters)
    {
        thrustPtr = thruster.get();
        if (glm::dot(thrustPtr->GetMaxBurnVector(), direction) > 0)
        {
            thrustPtr->DoBurn(throttle);
        }
    }
}

void SystemsComp::RotateTowardsTarget()
{
    Object* owner = mOwner.lock().get();
    if (mTargetForward == owner->GetForwardVec())
    {
        return;
    }

    mRotationSpeed = 0;
    for (auto& rcs : mReactionControls)
    {
        if (UseResource(rcs, rcs.get()->GetResourceType(), rcs.get()->GetUseRate()))
        {
            mRotationSpeed += rcs.get()->GetTurnSpeed();
        }
    }

    glm::vec3 crossNorm = glm::normalize(glm::cross(mTargetForward, owner->GetForwardVec()));

    //WE ARE ASSUMING BOTH VECTORS ARE NORMALIZED
    float angle = glm::acos(glm::dot(mTargetForward, owner->GetForwardVec()));

    if (angle < mRotationSpeed)
    {
        mRotationSpeed = angle;
    }

    glm::quat newRot = glm::angleAxis(mRotationSpeed, crossNorm);

    owner->SetRotation(owner->GetRotation() * newRot);
}

bool SystemsComp::FireWeapon()
{
    //TODO
    return false;
}

void SystemsComp::CycleWeapons()
{
    //TODO
}

bool SystemsComp::UseResource(std::shared_ptr<class MechModule> destModule, MechResource resource, float amount)
{
    for (auto& connection : mConnectionMatrix[destModule])
    {
        if (connection.second && connection.first.get()->RequestResource(resource, amount))
        {
            return true;
        }
    }
    //TODO recursive pass for more connections????
    return false;
}

void SystemsComp::OnCollision(std::weak_ptr<class Object> other)
{
}

void SystemsComp::Update(float deltaTime)
{
    Object* owner = mOwner.lock().get();
    if (mTargetForward != owner->GetForwardVec())
    {
        RotateTowardsTarget();
    }
}
