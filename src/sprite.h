#pragma once
#include <string>

using namespace std;

namespace graphics_manager {

struct Sprite {
    std::string image;
    float x;
    float y;
    float scale;
    float z;
};

}