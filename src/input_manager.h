#pragma once
#include "GLFW/glfw3.h"

namespace input_manager {

class InputManager {
    public:
        void Startup(GLFWwindow* window);
        void Shutdown();
        void Update(GLFWwindow* window);
        bool KeyIsPressed(GLFWwindow* window);
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

}