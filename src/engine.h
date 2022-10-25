#pragma once
#include <functional>
#include "graphics_manager.h"
#include "input_manager.h"
#include "sound_manager.h"
#include "resource_manager.h"
#include "script_manager.h"

#include "game.h"
#include "ecs.h"

namespace ingengine {

class Engine {
    public:
        typedef std::function<void()> UpdateCallback;
        Engine(game::Game* g);
        void Startup();
        void Shutdown();
        void RunGameLoop(const std::string& name, std::function<void()> callback = nullptr);
        int GetKey();
    private:
        ecs::ECS entity_manager;

        game::Game* game;

        graphics_manager::GraphicsManager graphics;
        input_manager::InputManager input;
        sound_manager::SoundManager sounds;
        resource_manager::ResourceManager resources;
        script_manager::ScriptManager scripts;


};

}