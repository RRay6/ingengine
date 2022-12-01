// #define GLFW_INCLUDE_NONE
#pragma once
#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
//#include "spdlog/spdlog.h"

// #define SOKOL_GLCORE33
// #include "sokol_gfx.h"

#include "engine.h"

#include "uniforms.h"

//#include <sokol_gfx.h>

#include "Components/sprite.h"

#include <vector>

#include <unordered_map>

using namespace std;

namespace graphics_manager {

struct Uniforms;



class GraphicsManager {
    friend class ecs::ECS;
    public:
        void Startup();
        void Shutdown();
        GLFWwindow* GetWindow();
        void Update();
        void ShouldQuit();
        static void WindowClosed(GLFWwindow* window);
        bool LoadImageA( const string& name, const string& path );
        void Draw(const std::vector< Sprite >& sprites); //const std::vector< Sprite >& sprites
        static void window_size_callback(GLFWwindow* window, int width, int height);
        void UpdateText(ecs::EntityID ent);
        //int MakePowerOfTwo(float ohDear);
        
        //void RenderText();
    private:
        GLFWwindow* window;
        int loaded = 0;
        
        //void IsFontLoad(const sfetch_response_t* response);
       // float lh;
       // float dpis;
       // unsigned int white, blue, black;
       // int atlas_dim;
};

}