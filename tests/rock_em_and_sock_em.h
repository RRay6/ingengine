#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>
#include <thread>
#include "../src/game.h"
#include "../src/ecs.h"
#include "../src/sound_manager.h"
#include "../src/resource_manager.h"
#include "../src/engine.h"

using namespace std;

namespace rock_em_and_sock_em {

class RockEmAndSockEm : public game::Game {
    public:
        virtual void Init();
        virtual void Input(int key);
        virtual void Update();
        void PlaySound();
    private:
        sound_manager::SoundManager sounds;
        resource_manager::ResourceManager resources;
    
    
};

}