#pragma once
#include <functional>
#include "graphics_manager.h"
#include "input_manager.h"
#include "sound_manager.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "entity_component_system.h"
#include <iostream>
#include <cstdint> // For int64_t

namespace ingengine {

struct EntityID {
    // The id is a 64-bit integer.
    typedef int64_t IDType;
    // Instance variable holding the actual ID, initialized to -1.
    IDType id{-1};
    // Construct this object with the actual ID.
    EntityID( IDType val ) : id(val) {}
    // We still want the default constructor.
    EntityID() = default;
    
    // This EntityID can convert itself to an int64_t on demand.
    operator IDType() { return id; }
    
    // This EntityID supports `.Get<Component>()`
    // The definition for this function declaration is below, since it uses the global ECS that hasn't been declared yet.
    template <typename T>
    T& Get();
};

// struct ECS {
//     template <typename T>
//     T& Get( EntityID ) { 
//         return GetAppropriateSparseSet<T>()[ entity ];
//     }
// };

struct ECS {
    template <typename T>
    T& Get( EntityID ) { static T val{}; return val; }
};

inline ECS ecs;

template <typename T> T& EntityID::Get() { return ecs.Get<T>(*this); }

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
        script_manager::ScriptManager scripts;


};

}