#pragma once
#include <functional>
#include "graphics_manager.h"
#include "input_manager.h"
#include "sound_manager.h"
#include "resource_manager.h"

namespace ingengine {

class Engine {
    public:
        static Engine* Instance() { return sInstance; }
        typedef std::function<void()> UpdateCallback;
        Engine();
        void Startup();
        void Shutdown();
        void RunGameLoop(const std::string& name, std::function<void()> callback = nullptr);
    private:
        static Engine* sInstance;

        graphics_manager::GraphicsManager graphics;
        input_manager::InputManager input;
        sound_manager::SoundManager sounds;
        resource_manager::ResourceManager resources;

};

}