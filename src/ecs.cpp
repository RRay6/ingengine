#include "ecs.h"
#include <iostream>
#include <cstdint> // For int64_t

namespace ecs {

EntityID ecs::ECS::Create()
{
    EntityID id;
    return id;
}

void ecs::ECS::Destroy( EntityID e ) {

}

}