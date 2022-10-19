#pragma once
#include "ecs.h"

struct Sprite
{
    std::string image;
    float x;
    float y;
    float scale;
    float z;

    int value{};
        
    // Let's make this Struct convert to and from ints for convenience, too.
    Sprite( int v ) : value( v ) {}
    operator int() { return value; }
    // Just because we have an int constructor doesn't mean we don't still want an empty constructor.
    Sprite() = default;
};