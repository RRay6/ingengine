#pragma once
#include <functional>
#include "graphics_manager.h"
#include "input_manager.h"
#include "sound_manager.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "types.h"
#include "game.h"
#include "ecs.h"

namespace ingengine {

class Engine {
    public:
        ecs::ECS entity_manager;
        input_manager::InputManager input;
        resource_manager::ResourceManager resources;

        typedef std::function<void()> UpdateCallback;
        Engine(game::Game* g);
        Engine();
        void Startup();
        void Shutdown();
        void RunGameLoop(const std::string& name, std::function<void()> callback = nullptr);
        int GetKey();
    private:
        game::Game* game;

        graphics_manager::GraphicsManager graphics;
        sound_manager::SoundManager sounds;
        script_manager::ScriptManager scripts;
        void TestTest();
        ecs::EntityID testEntity;

};
inline Engine gameEngine;
}