#pragma once

#include "ecs.h"
#include "Components/sprite.h"

namespace game {

class Game {
    public:
        // ecs::ECS
        ecs::ECS entity_manager;
        std::vector <Sprite> vec;
        std::vector <ecs::EntityID> entities;
        void PublicInit();
        void PublicInput(int key);
        void PublicUpdate();

    private:
        virtual void Init();
        virtual void Input(int key);
        virtual void Update();
        

};

}