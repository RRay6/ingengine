#pragma once
#include <iostream>
#include <string>

using namespace std;

namespace Types 
{
    typedef double real;
    typedef std::string string;

    struct Position { real x, y; }; // or: struct Position : public vec2 {};
    struct Velocity { real x, y; }; // or: struct Velocity : public vec2 {};
    struct Gravity { real meters_per_second; };
    // struct Sprite { string image; real size; };

    struct Health { real percent; };
    struct Script { string name; };
}