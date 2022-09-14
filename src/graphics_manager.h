// #define GLFW_INCLUDE_NONE
#pragma once
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

namespace graphics_manager {

class GraphicsManager {
    public:
        void Startup();
        void Shutdown();
        GLFWwindow* GetWindow();
        void Update();
        void ShouldQuit();
        static void WindowClosed(GLFWwindow* window);
};

}