#pragma once

#include <unordered_map>

#include "anax/System.hpp"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"

#include "components/PhysicsBodyComponent.h"
#include "components/TransformComponent.h"

class PhysicsWorldSystem
        : public anax::System<anax::Requires<PhysicsBodyComponent, TransformComponent>>
        , public b2ContactListener
{
public:
    PhysicsWorldSystem();
    ~PhysicsWorldSystem();

    void Integrate(double deltaTime);

    void BeginContact(b2Contact* contact) override {}
    void EndContact(b2Contact* contact) override {}
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {}

private:
    struct UserData
    {
        PhysicsBodyComponent::ContactType contactType;
        uint64_t entityId;
    };

    void initialize() override;
    void onEntityAdded(anax::Entity& entity) override;
    void onEntityRemoved(anax::Entity& entity) override;

    void OnPlayerBulletContact(const UserData* player, const UserData* bullet, b2Contact* contact);

    b2World m_world;
    typedef std::unordered_map<uint64_t, UserData*> UserDataMap;
    UserDataMap m_userDataMap;
};
