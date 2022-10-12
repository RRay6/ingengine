// #define GLFW_INCLUDE_NONE
#pragma once
#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

// #define SOKOL_GLCORE33
// #include "sokol_gfx.h"

#include "resource_manager.h"

#include "uniforms.h"

#include <sokol_gfx.h>

#include "Components/sprite.h"

#include <vector>

#include <unordered_map>

using namespace std;

namespace graphics_manager {

struct Uniforms;

struct Texture 
{
    sg_image image;
    int width;
    int height;
};

class GraphicsManager {
    public:
        void Startup();
        void Shutdown();
        GLFWwindow* GetWindow();
        void Update();
        void ShouldQuit();
        static void WindowClosed(GLFWwindow* window);
        bool LoadImage( const string& name, const string& path );
        void Draw(const std::vector< Sprite >& sprites); //const std::vector< Sprite >& sprites
        static void window_size_callback(GLFWwindow* window, int width, int height);
    private:
        GLFWwindow* window;
        resource_manager::ResourceManager resources;
        sg_pipeline pipeline;
        sg_pass_action pass_action{};
        sg_bindings bindings{};
        sg_shader_desc shader_desc{};
        unordered_map<string, Texture> umap;
        int loaded = 0;
};

}