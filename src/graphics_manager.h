// #define GLFW_INCLUDE_NONE
#pragma once
#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

// #define SOKOL_GLCORE33
// #include "sokol_gfx.h"

#include "uniforms.h"
#include "sprite.h"

using namespace std;

namespace graphics_manager {

struct Uniforms;

class GraphicsManager {
    public:
        void Startup();
        void Shutdown();
        GLFWwindow* GetWindow();
        void Update();
        void ShouldQuit();
        static void WindowClosed(GLFWwindow* window);
        bool LoadImage( const string& name, const string& path );
        void Draw(); //const std::vector< Sprite >& sprites
};

}