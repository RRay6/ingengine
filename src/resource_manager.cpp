#include "resource_manager.h"
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace resource_manager {

    std::filesystem::path ResourceManager::ResolvePath( const string& folder, const string& name ) {
        fs::path pl = fs::current_path();
        typedef std::filesystem::path path;

        std::string path_string{pl.u8string()};
        size_t found = path_string.find("\\build\\windows\\x64\\release");
        string r;

        if (found != string::npos)
        {
            r = path_string.substr(0, found);
        }

        const path root{ r };

        path p = root / "assets" / folder / name;

        //std::filesystem::path(path) / p.relative_path()

        return p;
    }
}