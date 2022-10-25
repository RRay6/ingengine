#pragma once
#include <sol/sol.hpp>
#include <string>
#include "resource_manager.h"
#include <iostream>
using namespace std;

namespace script_manager {

class ScriptManager {
    public:
        void Startup();
        void Shutdown();
        bool LoadScript( const string& name, const string& path );
    private:
        resource_manager::ResourceManager resources;
        sol::state lua;

};

}