#pragma once

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

    void Integrate(double deltaTime);

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
    void initialize() override;
    void onEntityAdded(anax::Entity& entity) override;
    void onEntityRemoved(anax::Entity& entity) override;

    b2World m_world;
};
