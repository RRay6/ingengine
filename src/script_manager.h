#pragma once
#include <sol/sol.hpp>
#include <string>
#include <iostream>
#include "resource_manager.h"
#include "input_manager.h"
#include "sound_manager.h"
using namespace std;

namespace script_manager {

class ScriptManager {
    public:
        void Startup();
        void Shutdown();
        bool LoadScript( const string& name, const string& path );
        void SetFun(input_manager::InputManager input);
        void SetFun(sound_manager::SoundManager input);
    private:
        resource_manager::ResourceManager resources;
        sol::state lua;

};

}