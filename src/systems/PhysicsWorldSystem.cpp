#include "PhysicsWorldSystem.h"

#include "CrazyBattle.h"
#include "Box2D/Box2D.h"

PhysicsWorldSystem::PhysicsWorldSystem()
    : m_world(b2Vec2(0.0f, 39.24f))
{
}

void PhysicsWorldSystem::Integrate(double deltaTime)
{
    const int32 VelocityIterations = 6;
    const int32 PositionIterations = 2;
    m_world.Step(static_cast<float32>(deltaTime), VelocityIterations, PositionIterations);

    for (const anax::Entity& entity : getEntities())
    {
        TransformComponent& transformComp = entity.getComponent<TransformComponent>();
        const PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

        const float PhysicsToPixels = 50.0f;

        transformComp.position.x = physicsBodyComp.params.body->GetPosition().x * PhysicsToPixels;
        transformComp.position.y = physicsBodyComp.params.body->GetPosition().y * PhysicsToPixels;
        transformComp.rotation = physicsBodyComp.params.body->GetAngle() * (180.0f / b2_pi);

        SDL_Rect rect;
        rect.w = physicsBodyComp.size.x * transformComp.scale.x;
        rect.h = physicsBodyComp.size.y * transformComp.scale.y;
        rect.x = transformComp.position.x;
        rect.y = transformComp.position.y;

        SDL_SetRenderDrawColor(CrazyBattle::Game().Renderer(), 0xff, 0xff, 0xff, 0xff);
        SDL_RenderDrawRect(CrazyBattle::Game().Renderer(), &rect);
    }
}

void PhysicsWorldSystem::initialize()
{
    m_world.SetContactListener(this);
}

void PhysicsWorldSystem::onEntityAdded(anax::Entity& entity)
{
    const float PixelsToPhysics = 0.02f;

    const TransformComponent& transformComp = entity.getComponent<TransformComponent>();
    PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();

    b2BodyDef bodyDef;
    bodyDef.type = physicsBodyComp.isStatic ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.x = (transformComp.position.x + physicsBodyComp.offset.x) * PixelsToPhysics;
    bodyDef.position.y = (transformComp.position.y + physicsBodyComp.offset.y) * PixelsToPhysics;
    bodyDef.angle = 0.0f;
    physicsBodyComp.params.body = m_world.CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    float32 width = physicsBodyComp.size.x * transformComp.scale.x * PixelsToPhysics / 2.0f;
    float32 height = physicsBodyComp.size.y * transformComp.scale.y * PixelsToPhysics / 2.0f;
    boxShape.SetAsBox(width, height, b2Vec2(width, height), 0.0f);

    b2FixtureDef boxFixture;
    boxFixture.shape = &boxShape;
    boxFixture.density = physicsBodyComp.density;
    boxFixture.friction = physicsBodyComp.friction;
    boxFixture.filter.groupIndex = physicsBodyComp.groupIndex;
    boxFixture.userData = nullptr;

    physicsBodyComp.params.body->CreateFixture(&boxFixture);
    physicsBodyComp.params.body->SetGravityScale(physicsBodyComp.hasGravity ? 1.0f : 0.0f);
    physicsBodyComp.params.body->SetBullet(physicsBodyComp.isBullet);
    physicsBodyComp.params.body->SetFixedRotation(!physicsBodyComp.canRotate);
}

void PhysicsWorldSystem::onEntityRemoved(anax::Entity& entity)
{
}

void PhysicsWorldSystem::BeginContact(b2Contact* contact)
{
}

void PhysicsWorldSystem::EndContact(b2Contact* contact)
{
}

void PhysicsWorldSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void PhysicsWorldSystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
