#include <iostream>
#include "engine.h"
#include "rock_em_and_sock_em.h"

int main( int argc, const char* argv[] ) {
    
    rock_em_and_sock_em::RockEmAndSockEm game;
    ingengine::Engine eng(&game);

    //eng.Init(&game);
    eng.Startup();
    std::cout << "Hello, ingENGINE! ...And the world I guess\n";
    return 0;
}