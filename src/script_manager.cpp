#include "script_manager.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace script_manager {

void ScriptManager::Startup() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
    
    // auto f = lua.load( R"(
    //     local a, b, c = ...
        
    //     print( a, b, c )
    // )" );
    
    // f( 10, "foo", "who", -1.5 ); // arguments
}

void ScriptManager::Shutdown() {

}

bool ScriptManager::LoadScript( const string& name, const string& path ) {


    // std::string path_string{resources.ResolvePath("sounds", "click.wav").u8string()};
    string path_string = resources.ResolvePath(path, name+".lua").u8string();
    cout << path_string << endl;

    sol::load_result script = lua.load_file( path_string );

    if (!script.valid()) 
    {
        return false;
	}

    // umap [ name ] = script;

    script();

    return true;
}

void ScriptManager::SetFun(input_manager::InputManager input)
{
    lua.set_function( "KeyIsDown", [&]( const int keycode ) { return input.KeyIsDown( keycode ); } );
}

void ScriptManager::SetFun(sound_manager::SoundManager input)
{
    lua.set_function( "PlaySound", [&]( const string sound ) { string path_string = resources.ResolvePath("sounds", sound).u8string(); return input.LoadSound( sound,  path_string); } );
}

}