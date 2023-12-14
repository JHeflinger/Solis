#pragma once
#include <string>
#include <vector>

namespace Solis {
    class FileUtils {
    public:
        static std::vector<char> Read(const std::string& filename);
        static std::vector<std::string> List(const std::string& dirname = ".");
    };
}