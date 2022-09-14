#include "graphics_manager.h"
#include <iostream>
#include <string>

namespace graphics_manager {

    GLFWwindow* window;

void GraphicsManager::Startup()
{
    int window_width = 100;
    int window_height = 100;
    // std::string window_name = "ingengine";
    bool window_fullscreen = false;

    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    window = glfwCreateWindow( window_width, window_height, "ingengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0 );
    glfwSetWindowAspectRatio( window, window_width, window_height );
    
    if( !window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        //std::cout << "Failed to create a window.\n";
        glfwTerminate();
    }
    // else
    // {
    //     std::cerr << "It's good." << std::endl;
    // }

    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);
    //glfwPollEvents();

    glfwSetWindowCloseCallback(window, WindowClosed);

    //glfwTerminate();
}

void GraphicsManager::Update() {
    // if (!glfwWindowShouldClose(window)) {
        
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();

    //     glfwSetWindowCloseCallback(window, WindowClosed);
    // }
}

void GraphicsManager::Shutdown() {

}

GLFWwindow* GraphicsManager::GetWindow() {
    return window;
}

void GraphicsManager::ShouldQuit() {
    //glfwSetWindowCloseCallback(window, glfwWindowCloseCallback(window));
    glfwWindowShouldClose(window);
}

void GraphicsManager::WindowClosed(GLFWwindow* window)
{
    std::cerr << "Close." << std::endl;
    glfwSetWindowShouldClose(window, true);
    glfwTerminate();
}

}