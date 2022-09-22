#include "engine.h"
#include <thread>
#include <chrono>
#include <iostream>

namespace ingengine {

    Engine* ingengine::Engine::sInstance = nullptr;

Engine::Engine() {
    assert(sInstance == nullptr);
    sInstance = this;
}

void Engine::Startup() {

    // std::cerr << resources.ResolvePath("sounds", "click.wav") << std::endl;

    graphics.Startup();
    input.Startup(graphics.GetWindow());
    sounds.Startup();
    RunGameLoop("Start");
}

void Engine::Shutdown() {
    graphics.Shutdown();
    input.Shutdown();
}

void Engine::RunGameLoop(const std::string& name, std::function<void()> callback) {
    
    auto prev  = std::chrono::steady_clock::now();
    auto accumulator = std::chrono::duration<double>( 0 );
    while(true)
    {
        auto curr = std::chrono::steady_clock::now();
        auto delta = curr - prev;
        prev = curr;
        accumulator += delta;

        while (accumulator > std::chrono::duration<double>( 1.0 / 61.0 ))
        {
            //Do something
            // std::cerr << "Test." << std::endl;
            input.Update(graphics.GetWindow());
            // graphics.Update();
            //std::string path_string{path.u8string()}

            // if (input.KeyIsPressed(graphics.GetWindow()) == true) {
            //     std::string path_string{resources.ResolvePath("click.wav").u8string()};
            //     sounds.LoadSound("click.wav", path_string);
            // }

            accumulator -= std::chrono::duration<double>( 1.0 / 59.0 );

            if (accumulator < std::chrono::duration<double>( 0 ))
            {
                accumulator = std::chrono::duration<double>( 0 );
            }
        }
    } 
}

}
