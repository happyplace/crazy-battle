#pragma once

#include "anax/Component.hpp"
#include "Box2D/Dynamics/b2Body.h"

struct PhysicsBodyComponent : anax::Component
{
    enum class ContactType
    {
        Generic,
        Player,
        Bullet,
        Floor,
    };

    enum class BodyType { Box, };

    struct PhysicsBodyParams
    {
        PhysicsBodyParams() : body(nullptr) {}
        b2Body* body;
    };

    PhysicsBodyComponent()
        : isStatic(false), size(0.0f, 0.0f), density(1.0f)
        , friction(0.3f), hasGravity(true), offset(0.0f, 0.0f)
        , groupIndex(0), isBullet(false), canRotate(false)
        , bodyType(BodyType::Box), contactType(ContactType::Generic)
    {}

    PhysicsBodyParams params;
    bool isStatic;
    b2Vec2 size;
    float density;
    float friction;
    bool hasGravity;
    b2Vec2 offset;
    int16_t groupIndex;
    bool isBullet;
    bool canRotate;
    BodyType bodyType;
    ContactType contactType;
};
