#include "sound_manager.h"
#include <string> 
#include <iostream>

namespace sound_manager {

    SoLoud::Soloud soloud;
    //std::unordered_map< string, SoLoud::Wav > map;

void SoundManager::Startup() {
    //SoundManager::SoLoud().init();
    //soloud.init();
}

void SoundManager::Shutdown() {
    //SoundManager::SoLoud().deinit();
    soloud.deinit();
}

bool SoundManager::LoadSound( const string& name, const string& path ) {
    //std::unordered_map< string, SoLoud::Wav > map;

    // SoundManager::Map()[ name ].load( path.c_str() );
    // SoundManager::SoLoud().play( SoundManager::Map()[ name ] );
    // SoundManager::Map().erase( name );

    // map[ name ].load( path.c_str() );
    // soloud.play( map[ name ] );
    // map.erase( name );

    SoLoud::Wav wave;
    //SoLoud::Speech speech;

    //speech.setText("1 2 3   1 2 3   Hello world. Welcome to So-Loud.");

    soloud.init();
    wave.load(path.c_str());
    int handle = soloud.play(wave);

    std::string s = std::to_string(handle);
    std::cerr << s << std::endl;

    
    while (soloud.getActiveVoiceCount() > 0)
    {
        
    }

    soloud.deinit();


    return 1;
}

}