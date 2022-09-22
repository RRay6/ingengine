#pragma once
#include <filesystem>
#include <string>
using namespace std;

namespace resource_manager {

class ResourceManager {
    public:
        std::filesystem::path ResourceManager::ResolvePath( const string& folder, const string& name );

};

}