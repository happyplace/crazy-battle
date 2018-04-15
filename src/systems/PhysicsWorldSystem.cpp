#include "PhysicsWorldSystem.h"

#include "anax/World.hpp"
#include "Box2D/Box2D.h"

#include "CrazyBattle.h"

#include "components/AttackComponent.h"
#include "components/PlayerComponent.h"
#include "components/PlayerDamageComponent.h"
#include "components/TextureComponent.h"
#include "components/AnimatedSpriteComponent.h"
#include "AssetLoaderHelper.h"
#include "components/TimedLifeComponent.h"
#include "components/LinearAttackComponent.h"

PhysicsWorldSystem::PhysicsWorldSystem()
    : m_world(b2Vec2(0.0f, 39.24f))
{
    m_texture = AssetLoaderHelper::LoadTexture("media/opp2/opp2_sprites.png");
    m_textureFrames = AssetLoaderHelper::LoadTextureFrames("media/opp2_sprites.json");
    m_spriteAnimations = AssetLoaderHelper::LoadSpriteAnimations("media/opp2_animations.json");
}

PhysicsWorldSystem::~PhysicsWorldSystem()
{
    for(auto& userData : m_userDataMap)
    {
        delete userData.second;
    }
    m_userDataMap.clear();
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
        transformComp.position.x += physicsBodyComp.offset.x;
        transformComp.position.y = physicsBodyComp.params.body->GetPosition().y * PhysicsToPixels;
        transformComp.position.y += physicsBodyComp.offset.y;
        transformComp.rotation = physicsBodyComp.params.body->GetAngle() * (180.0f / b2_pi);

        SDL_Rect rect;
        rect.w = physicsBodyComp.size.x * transformComp.scale.x;
        rect.h = physicsBodyComp.size.y * transformComp.scale.y;
        rect.x = physicsBodyComp.params.body->GetPosition().x * PhysicsToPixels;
        rect.y = physicsBodyComp.params.body->GetPosition().y * PhysicsToPixels;

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
    UserData* userData = new UserData();
    userData->contactType = physicsBodyComp.contactType;
    userData->entityId = entity.getId().index;
    boxFixture.userData = userData;
    if (physicsBodyComp.category != 0)
        boxFixture.filter.categoryBits = physicsBodyComp.category;
    m_userDataMap[userData->entityId] = userData;

    physicsBodyComp.params.body->CreateFixture(&boxFixture);
    physicsBodyComp.params.body->SetGravityScale(physicsBodyComp.hasGravity ? 1.0f : 0.0f);
    physicsBodyComp.params.body->SetBullet(physicsBodyComp.isBullet);
    physicsBodyComp.params.body->SetFixedRotation(!physicsBodyComp.canRotate);
}

void PhysicsWorldSystem::onEntityRemoved(anax::Entity& entity)
{
    delete m_userDataMap[entity.getId().index];
    m_userDataMap.erase(entity.getId().index);
    PhysicsBodyComponent& physicsBodyComp = entity.getComponent<PhysicsBodyComponent>();
    m_world.DestroyBody(physicsBodyComp.params.body);
}

void PhysicsWorldSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    UserData* userDataA = static_cast<UserData*>(contact->GetFixtureA()->GetUserData());
    UserData* userDataB = static_cast<UserData*>(contact->GetFixtureB()->GetUserData());
    PhysicsBodyComponent::ContactType contactTypeA = userDataA->contactType;
    PhysicsBodyComponent::ContactType contactTypeB = userDataB->contactType;

    if (contactTypeA == PhysicsBodyComponent::ContactType::Player &&
        contactTypeB == PhysicsBodyComponent::ContactType::Bullet)
    {
        OnPlayerBulletContact(userDataA, userDataB, contact);
    }
    else if (contactTypeA == PhysicsBodyComponent::ContactType::Bullet &&
             contactTypeB == PhysicsBodyComponent::ContactType::Player)
    {
        OnPlayerBulletContact(userDataB, userDataA, contact);
    }
    else if (contactTypeA == PhysicsBodyComponent::ContactType::Bullet &&
             contactTypeB == PhysicsBodyComponent::ContactType::Bullet)
    {
        OnBulletBulletContact(userDataA, userDataB, contact);
    }
    else if (contactTypeA == PhysicsBodyComponent::ContactType::Bullet &&
             contactTypeB == PhysicsBodyComponent::ContactType::Floor)
    {
        OnBulletFloorContact(userDataA);
    }
    else if (contactTypeA == PhysicsBodyComponent::ContactType::Floor &&
             contactTypeB == PhysicsBodyComponent::ContactType::Bullet)
    {
        OnBulletFloorContact(userDataB);
    }
}

void PhysicsWorldSystem::OnPlayerBulletContact(const UserData* player, const UserData* bullet, b2Contact* contact)
{
    int64_t playerPlayerId = getWorld().getEntity(player->entityId).getComponent<PlayerComponent>().player.id;
    int64_t bulletPlayerId = getWorld().getEntity(bullet->entityId).getComponent<AttackComponent>().ownerPlayerId;

    contact->SetEnabled(false);

    if (playerPlayerId != bulletPlayerId)
    {
        anax::Entity bulletEntity = getWorld().getEntity(bullet->entityId);

        TransformComponent& bulletTransformComp = bulletEntity.getComponent<TransformComponent>();

        anax::Entity bulletHitEntity = getWorld().createEntity();
        TransformComponent& bulletHitTransformComp = bulletHitEntity.addComponent<TransformComponent>();
        bulletHitTransformComp.position = bulletTransformComp.position;
        TextureComponent& bulletHitTextureComp = bulletHitEntity.addComponent<TextureComponent>();
        bulletHitTextureComp.texture = m_texture;
        bulletHitTextureComp.textureFrames = m_textureFrames;
        AnimatedSpriteComponent& bulletHitAnimatedSpriteComp = bulletHitEntity.addComponent<AnimatedSpriteComponent>();
        bulletHitAnimatedSpriteComp.spriteAnimationsAsset = m_spriteAnimations;
        bulletHitAnimatedSpriteComp.animationName = "fx_explosion_b_anim";
        bulletHitEntity.addComponent<TimedLifeComponent>().timeLeftToKeepAlive = 0.45f;
        bulletHitEntity.activate();

        anax::Entity damageEntity = getWorld().createEntity();
        PlayerDamageComponent& playerDamageComponent = damageEntity.addComponent<PlayerDamageComponent>();
        if (bulletEntity.hasComponent<LinearAttackComponent>())
            playerDamageComponent.damageType = DamageType::Linear;
        else
            SDL_assert(false);
        playerDamageComponent.receiverPlayerId = playerPlayerId;
        playerDamageComponent.senderPlayerId = bulletPlayerId;
        damageEntity.activate();

        getWorld().getEntity(bullet->entityId).kill();
    }
}

void PhysicsWorldSystem::OnBulletBulletContact(const UserData* bulletA, const UserData* bulletB, b2Contact* contact)
{
    int64_t bulletAPlayerId = getWorld().getEntity(bulletA->entityId).getComponent<AttackComponent>().ownerPlayerId;
    int64_t bulletBPlayerId = getWorld().getEntity(bulletB->entityId).getComponent<AttackComponent>().ownerPlayerId;

    contact->SetEnabled(false);
    if (bulletAPlayerId != bulletBPlayerId)
    {
        TransformComponent& bulletTransformCompA = getWorld().getEntity(bulletA->entityId).getComponent<TransformComponent>();

        anax::Entity bulletHitEntityA = getWorld().createEntity();
        TransformComponent& bulletHitTransformCompA = bulletHitEntityA.addComponent<TransformComponent>();
        bulletHitTransformCompA.position = bulletTransformCompA.position;
        TextureComponent& bulletHitTextureCompA = bulletHitEntityA.addComponent<TextureComponent>();
        bulletHitTextureCompA.texture = m_texture;
        bulletHitTextureCompA.textureFrames = m_textureFrames;
        AnimatedSpriteComponent& bulletHitAnimatedSpriteCompA = bulletHitEntityA.addComponent<AnimatedSpriteComponent>();
        bulletHitAnimatedSpriteCompA.spriteAnimationsAsset = m_spriteAnimations;
        bulletHitAnimatedSpriteCompA.animationName = "fx_explosion_b_anim";
        bulletHitEntityA.addComponent<TimedLifeComponent>().timeLeftToKeepAlive = 0.45f;
        bulletHitEntityA.activate();

        TransformComponent& bulletTransformCompB = getWorld().getEntity(bulletB->entityId).getComponent<TransformComponent>();

        anax::Entity bulletHitEntityB = getWorld().createEntity();
        TransformComponent& bulletHitTransformCompB = bulletHitEntityB.addComponent<TransformComponent>();
        bulletHitTransformCompB.position = bulletTransformCompB.position;
        TextureComponent& bulletHitTextureCompB = bulletHitEntityB.addComponent<TextureComponent>();
        bulletHitTextureCompB.texture = m_texture;
        bulletHitTextureCompB.textureFrames = m_textureFrames;
        AnimatedSpriteComponent& bulletHitAnimatedSpriteCompB = bulletHitEntityB.addComponent<AnimatedSpriteComponent>();
        bulletHitAnimatedSpriteCompB.spriteAnimationsAsset = m_spriteAnimations;
        bulletHitAnimatedSpriteCompB.animationName = "fx_explosion_b_anim";
        bulletHitEntityB.addComponent<TimedLifeComponent>().timeLeftToKeepAlive = 0.45f;
        bulletHitEntityB.activate();

        getWorld().getEntity(bulletA->entityId).kill();
        getWorld().getEntity(bulletB->entityId).kill();
    }
}

void PhysicsWorldSystem::OnBulletFloorContact(const UserData* bullet)
{
    TransformComponent& bulletTransformComp = getWorld().getEntity(bullet->entityId).getComponent<TransformComponent>();

    anax::Entity bulletHitEntity = getWorld().createEntity();
    TransformComponent& bulletHitTransformComp = bulletHitEntity.addComponent<TransformComponent>();
    bulletHitTransformComp.position = bulletTransformComp.position;
    TextureComponent& bulletHitTextureComp = bulletHitEntity.addComponent<TextureComponent>();
    bulletHitTextureComp.texture = m_texture;
    bulletHitTextureComp.textureFrames = m_textureFrames;
    AnimatedSpriteComponent& bulletHitAnimatedSpriteComp = bulletHitEntity.addComponent<AnimatedSpriteComponent>();
    bulletHitAnimatedSpriteComp.spriteAnimationsAsset = m_spriteAnimations;
    bulletHitAnimatedSpriteComp.animationName = "fx_explosion_b_anim";
    bulletHitEntity.addComponent<TimedLifeComponent>().timeLeftToKeepAlive = 0.45f;
    bulletHitEntity.activate();

    getWorld().getEntity(bullet->entityId).kill();
}
