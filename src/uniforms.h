#pragma once

#include "glm/glm.hpp"

namespace graphics_manager {

struct Uniforms {
    glm::mat4 projection;
    glm::mat4 transform;
};

}