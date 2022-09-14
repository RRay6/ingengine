#include <iostream>
#include "engine.h"

int main( int argc, const char* argv[] ) {
    ingengine::Engine eng;
    eng.Startup();
    std::cout << "Hello, ingENGINE! ...And the world I guess\n";
    return 0;
}