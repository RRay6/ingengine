#include "input_manager.h"
#include <iostream>

namespace input_manager {

    int current_key = -1;
    bool pressed = false;

void InputManager::Startup(GLFWwindow* window) {

    glfwSetKeyCallback(window, KeyCallback);
    sounds.Startup();
    //sound.Startup();
}

void InputManager::Shutdown() {

}

void InputManager::Update(GLFWwindow* window) {
    glfwPollEvents(); 
    //KeyIsPressed(window);
}

int InputManager::KeyPressed(GLFWwindow* window) {
    if(glfwGetKey(window, 263)) 
    {
        // std::cerr << "Key pressed sound." << std::endl;
        return 0;
    }

    return 0;
}

int InputManager::GetKey()
{
    if (pressed)
    {
        return current_key;
    }
    else
    {
        return -1;
    }
}

bool InputManager::KeyIsDown(int keycode)
{
    return (GetKey() == keycode);
}

void InputManager::SetPressedFalse()
{
    pressed = false;
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS) {
        
        // std::cerr << "Key pressed." << std::endl;
        // std::string path_string{resources.ResolvePath("sounds", "click.wav").u8string()};
        // sounds.LoadSound("click.wav", path_string);

        current_key = key;
        pressed = true;
    }

    //std::cerr << "Key pressed." << std::endl;
}

}