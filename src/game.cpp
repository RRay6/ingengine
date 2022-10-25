#include "game.h"

#include "Components/sprite.h"

namespace game {

void game::Game::PublicInit()
{
    Init();
}

void game::Game::PublicInput(int key)
{
    Input(key);
}

void game::Game::PublicUpdate()
{
    Update();
}

void game::Game::Init()
{

}

void game::Game::Input(int key)
{

}

void game::Game::Update()
{
    cout << "TESTTTTTT 2: \n";
}

}