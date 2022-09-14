#pragma once
#include "soloud.h"
#include "soloud_wav.h"
#include <unordered_map>
#include <string>
using namespace std;

namespace sound_manager {

class SoundManager {
    public:
        //static SoLoud::Soloud SoLoud() { return soloud; }
        //static std::unordered_map< string, SoLoud::Wav > Map() { return map; }
        void Startup();
        void Shutdown();
        bool LoadSound( const string& name, const string& path );
    private:
        //static SoLoud::Soloud soloud;
        //static std::unordered_map< string, SoLoud::Wav > map;
};

}