#include "gf/GameMode.h"

#include "gf/systems/SpriteRendererSystem.h"

using namespace gf;

GameMode::GameMode()
	: m_entities(m_events)
	, m_systems(m_entities, m_events)
{
}

void GameMode::Init()
{
	m_systems.add<SpriteRendererSystem>();

	//OnInit();

	m_systems.configure();
}

void GameMode::Update()
{
	m_systems.update_all(0.16);

	//OnUpdate();
}

void GameMode::Destroy()
{
}

