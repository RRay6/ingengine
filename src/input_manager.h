#pragma once
#include "GLFW/glfw3.h"
#include "sound_manager.h"
#include "resource_manager.h"

namespace input_manager {

class InputManager {
    public:
        void Startup(GLFWwindow* window);
        void Shutdown();
        void Update(GLFWwindow* window);
        int KeyPressed(GLFWwindow* window);
        int GetKey();
        void SetPressedFalse();
        bool KeyIsDown(int keycode);
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
        sound_manager::SoundManager sounds;
        resource_manager::ResourceManager resources;
};

}