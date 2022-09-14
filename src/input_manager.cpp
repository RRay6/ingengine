#include "input_manager.h"
#include <iostream>
#include "sound_manager.h"
#include "resource_manager.h"

namespace input_manager {

    sound_manager::SoundManager sounds;
    resource_manager::ResourceManager resources;

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

bool InputManager::KeyIsPressed(GLFWwindow* window) {
    if(glfwGetKey(window, 263)) {
        std::cerr << "Key pressed sound." << std::endl;
        return true;
    }

    return false;
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == 263 && action == GLFW_PRESS) {
        std::cerr << "Key pressed." << std::endl;
        std::string path_string{resources.ResolvePath("click.wav").u8string()};
        sounds.LoadSound("click.wav", path_string);
    }
}

}