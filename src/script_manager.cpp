#include "script_manager.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace script_manager {

void ScriptManager::Startup() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
}

void ScriptManager::Shutdown() {

}

bool ScriptManager::LoadScript( const string& name, const string& path ) {

    return false;
}

}