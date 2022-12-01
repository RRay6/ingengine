#include "engine.h"
#include <thread>
#include <chrono>
#include <iostream>

#include "Components/sprite.h"
#include "Components/foo.h"

namespace ingengine {

    void Engine::TestTest() {
        string theTxt = "Please work.";
        Types::Text testing{ theTxt, 50, 50 };
        testEntity = gameEngine.entity_manager.Create();
        gameEngine.entity_manager.Get<Types::Text>(testEntity) = testing;
    }

Engine::Engine(game::Game* g) :
    Engine::game(g)
{
}

Engine::Engine() {

}

void Engine::Startup() {

    // std::cerr << resources.ResolvePath("sounds", "click.wav") << std::endl;

    // ecs::EntityID a(1);

    // //a.Get<Sprite>() = 7;
    // a.Get<Sprite>().x = 16;
    // cout << "a.Get<Sprite>(): " << a.id << " " << a.Get<Sprite>().x << '\n';

    // entity_manager.Create();

    // newPlayer.addComponent<Sprite>();

    // Engine::game->Init();

    graphics.Startup();
    input.Startup(graphics.GetWindow());
    sounds.Startup();
    scripts.Startup();

    Engine::game->PublicInit();

    scripts.SetFun(input);
    scripts.SetFun(sounds);

    TestTest();
    RunGameLoop("Start");
}

void Engine::Shutdown() {
    graphics.Shutdown();
    input.Shutdown();
}

int Engine::GetKey()
{
    return input.GetKey();
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
            graphics.UpdateText(testEntity);
            // Sprite sprite;
            // sprite.image = "lulu_the_cat.jpg";
            // sprite.scale = 100;
            // sprite.x = 1;
            // sprite.y = 1;
            // sprite.z = 1;

            // Sprite sprite2;
            // sprite2.image = "penguin.png";
            // sprite2.scale = 50;
            // sprite2.x = 20;
            // sprite2.y = 1;
            // sprite2.z = 1;

            // std::vector <Sprite> sprites = { sprite, sprite2 };


            // graphics.Update();


            //std::string path_string{path.u8string()}

            // if (input.KeyPressed(graphics.GetWindow()) == true) {
            //     std::string path_string{resources.ResolvePath("click.wav").u8string()};
            //     sounds.LoadSound("click.wav", path_string);
            // }

            Engine::game->PublicInput(input.GetKey());
            Engine::game->PublicUpdate();
            graphics.Draw(Engine::game->vec);

            //graphics.RenderText();

            if (input.GetKey() != -1)
            {
                // cout << "Key Pressed: " << key << '\n';
                input.SetPressedFalse();
            }

            accumulator -= std::chrono::duration<double>( 1.0 / 59.0 );

            if (accumulator < std::chrono::duration<double>( 0 ))
            {
                accumulator = std::chrono::duration<double>( 0 );
            }
        }
    } 
}

}
