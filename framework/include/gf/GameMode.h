#pragma once

#include "entityx/Entity.h"
#include "entityx/Event.h"
#include "entityx/System.h"
#include "entityx/config.h"

#include "FrameworkExport.h"

namespace gf
{
    class GameMode
    {
    public:
        GameMode();
        virtual ~GameMode() {}

        void Init();
        void Update();
        void Destroy();

        //virtual void OnInit() = 0;
        //virtual void OnUpdate() = 0;
        //virtual void OnDestroy() = 0;

	protected:
		entityx::EventManager m_events;
		entityx::EntityManager m_entities;
		entityx::SystemManager m_systems;
    };
}
