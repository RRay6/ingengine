#include <iostream>
#include "engine.h"
#include "scurvy.h"

int main( int argc, const char* argv[] ) {
    
    scurvy::Scurvy game;
    ingengine::Engine eng(&game);

    //eng.Init(&game);
    eng.Startup();
    std::cout << "Hello, ingENGINE! ...And the world I guess\n";
    return 0;
}