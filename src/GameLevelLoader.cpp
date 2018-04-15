#include "GameLevelLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SDL.h>

#include "anax/World.hpp"

#include "components/PhysicsBodyComponent.h"
#include "components/TransformComponent.h"
#include "components/TextureComponent.h"
#include "components/SpriteComponent.h"
#include "AssetLoaderHelper.h"

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
                else if (strcmp(componentType, "sprite") == 0)
                {
                    LoadSprite(entity, components[k]);
                }
			}
            entity.activate();
		}
	}
}

void GameLevelLoader::LoadPhysicsBody(anax::Entity& entity, const rapidjson::Value& json) const
{
    PhysicsBodyComponent& physicsBodyComp = entity.addComponent<PhysicsBodyComponent>();

    physicsBodyComp.isStatic = true;
    physicsBodyComp.density = 1.0f;
    physicsBodyComp.hasGravity = false;
    physicsBodyComp.friction = 0.3f;
    physicsBodyComp.offset.x = 0.0f;
    physicsBodyComp.offset.y = 0.0f;
    physicsBodyComp.groupIndex = 0;
    physicsBodyComp.isBullet = false;
    physicsBodyComp.canRotate = false;
    physicsBodyComp.bodyType = PhysicsBodyComponent::BodyType::Box;
    physicsBodyComp.contactType = PhysicsBodyComponent::ContactType::Floor;

    physicsBodyComp.size.x = json["size"]["width"].GetFloat();
    physicsBodyComp.size.y = json["size"]["height"].GetFloat();

    if (json.HasMember("is_static"))
        physicsBodyComp.isStatic = json["is_static"].GetBool();
    if (json.HasMember("density"))
        physicsBodyComp.density = json["density"].GetFloat();
    if (json.HasMember("friction"))
        physicsBodyComp.friction = json["friction"].GetFloat();
    if (json.HasMember("has_gravity"))
        physicsBodyComp.hasGravity = json["has_gravity"].GetBool();
    if (json.HasMember("offset"))
    {
        if (json["offset"].HasMember("x"))
            physicsBodyComp.offset.x = json["offset"]["x"].GetFloat();
        if (json["offset"].HasMember("y"))
            physicsBodyComp.offset.y = json["offset"]["y"].GetFloat();
    }
    if (json.HasMember("group_index"))
        physicsBodyComp.groupIndex = json["group_index"].GetInt();
    if (json.HasMember("is_bullet"))
        physicsBodyComp.isBullet = json["is_bullet"].GetBool();
    if (json.HasMember("can_rotate"))
        physicsBodyComp.canRotate = json["can_rotate"].GetBool();
    if (json.HasMember("body_type"))
    {
        const char* bodyType = json["body_type"].GetString();
        if (strcmp(bodyType, "box") == 0)
            physicsBodyComp.bodyType = PhysicsBodyComponent::BodyType::Box;
    }
}

void GameLevelLoader::LoadTransform(anax::Entity& entity, const rapidjson::Value& json) const
{
    TransformComponent& transformComp = entity.addComponent<TransformComponent>();
    transformComp.position.x = json["position"]["x"].GetFloat();
    transformComp.position.y = json["position"]["y"].GetFloat();
    if (json.HasMember("rotation"))
        transformComp.rotation = json["rotation"].GetFloat();
    if (json.HasMember("scale"))
    {
        if (json["scale"].HasMember("x"))
            transformComp.scale.x = json["scale"]["x"].GetFloat();
        if (json["scale"].HasMember("y"))
            transformComp.scale.y = json["scale"]["y"].GetFloat();
    }
    if (json.HasMember("flip_horizontal"))
        transformComp.flipHorizontal = json["flip_horizontal"].GetBool();
    if (json.HasMember("flip_vertical"))
        transformComp.flipVertical = json["flip_vertical"].GetBool();
}

void GameLevelLoader::LoadSprite(anax::Entity& entity, const rapidjson::Value& json) const
{
    TextureComponent& textureComp = entity.addComponent<TextureComponent>();
    std::string texture = "media/";
    texture.append(json["texture"].GetString());
    textureComp.texture = AssetLoaderHelper::LoadTexture(texture.c_str());
    std::string frames = "media/";
    frames.append(json["frames"].GetString());
    textureComp.textureFrames = AssetLoaderHelper::LoadTextureFrames(frames.c_str());

    SpriteComponent& spriteComp = entity.addComponent<SpriteComponent>();
    if (json.HasMember("frame"))
        spriteComp.frameName = json["frame"].GetString();
}
