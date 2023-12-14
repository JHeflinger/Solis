#include "FileUtils.h"
#include <fstream>
#include <filesystem>

#ifdef NDEBUG
    #define SANDBOX ""
#else
    #define SANDBOX "../../../../../" // note: doing this because bazel sandbox is quite a few layers deep
#endif

namespace Solis {

    std::vector<char> FileUtils::Read(const std::string& filename) {
        std::ifstream file(SANDBOX + filename, std::ios::ate | std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file \"" + filename + "\"");
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }

    std::vector<std::string> FileUtils::List(const std::string& dirname) {
        std::vector<std::string> contents;
        try {
            for (const auto& entry : std::filesystem::directory_iterator((SANDBOX + dirname).c_str()))
                contents.push_back(entry.path().filename());
        } catch (const std::filesystem::filesystem_error& ex) {
            throw std::runtime_error("Failed to open directory \"" + dirname + "\"");
        }
        return contents;
    }

}