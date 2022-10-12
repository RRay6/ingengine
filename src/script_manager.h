#pragma once
#include <sol/sol.hpp>
#include <string>
using namespace std;

namespace script_manager {

class ScriptManager {
    public:
        void Startup();
        void Shutdown();
        bool LoadScript( const string& name, const string& path );
    private:
        sol::state lua;

};

}