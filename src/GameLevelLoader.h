#pragma once

#include "rapidjson/document.h"

namespace anax
{
    class World;
    class Entity;
}

class GameLevelLoader
{
public:
	void LoadLevel(anax::World& world, const char* jsonPath) const;

private:
    void LoadPhysicsBody(anax::Entity& entity, const rapidjson::Value& json) const;
    void LoadTransform(anax::Entity& entity, const rapidjson::Value& json) const;
};
