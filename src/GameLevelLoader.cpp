#include "GameLevelLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SDL.h>

#include "anax/World.hpp"

#include "components/PhysicsBodyComponent.h"
#include "components/TransformComponent.h"

using namespace anax;
using namespace rapidjson;

void GameLevelLoader::LoadLevel(anax::World& world, const char* jsonPath) const
{
	std::ifstream levelFile(jsonPath);
	if (levelFile.is_open())
	{
		std::string line;
		std::stringstream levelRawText;
		while (getline(levelFile, line))
		{
			levelRawText << line;
		}
		levelFile.close();

		Document levelDoc;
		levelDoc.Parse(levelRawText.str().c_str());

		for (SizeType i = 0; i < levelDoc.Size(); i++)
		{
            Entity entity = world.createEntity();
			const Value& components = levelDoc[i]["components"];
			for (SizeType k = 0; k < components.Size(); k++)
			{
                SDL_assert(components[k].HasMember("type"));
                SDL_assert(components[k]["type"].IsString());
                const char* componentType = components[k]["type"].GetString();
                if (strcmp(componentType, "physics_body") == 0)
				{
                    LoadPhysicsBody(entity, components[k]);
				}
                else if (strcmp(componentType, "transform") == 0)
                {
                    LoadTransform(entity, components[k]);
                }
			}
            entity.activate();
		}
	}
}

void GameLevelLoader::LoadPhysicsBody(anax::Entity& entity, const rapidjson::Value& json) const
{
    PhysicsBodyComponent& physicsBodyComp = entity.addComponent<PhysicsBodyComponent>();
    physicsBodyComp.isStatic = json["is_static"].GetBool();
    physicsBodyComp.size.x = json["size"]["width"].GetFloat();
    physicsBodyComp.size.y = json["size"]["height"].GetFloat();
    physicsBodyComp.density = json["density"].GetFloat();
    physicsBodyComp.friction = json["friction"].GetFloat();
    physicsBodyComp.hasGravity = json["has_gravity"].GetBool();
    physicsBodyComp.offset.x = json["offset"]["x"].GetFloat();
    physicsBodyComp.offset.y = json["offset"]["y"].GetFloat();
    physicsBodyComp.groupIndex = json["group_index"].GetInt();
    physicsBodyComp.isBullet = json["is_bullet"].GetBool();
    physicsBodyComp.canRotate = json["can_rotate"].GetBool();

    const char* bodyType = json["body_type"].GetString();
    if (strcmp(bodyType, "box") == 0)
        physicsBodyComp.bodyType = PhysicsBodyComponent::BodyType::Box;
}

void GameLevelLoader::LoadTransform(anax::Entity& entity, const rapidjson::Value& json) const
{
    TransformComponent& transformComp = entity.addComponent<TransformComponent>();
    transformComp.position.x = json["position"]["x"].GetFloat();
    transformComp.position.y = json["position"]["y"].GetFloat();
    transformComp.rotation = json["rotation"].GetFloat();
    transformComp.scale.x = json["scale"]["x"].GetFloat();
    transformComp.scale.y = json["scale"]["y"].GetFloat();
    transformComp.flipHorizontal = json["flip_horizontal"].GetBool();
    transformComp.flipVertical = json["flip_vertical"].GetBool();
}
