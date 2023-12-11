#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

namespace Solis {
    class Renderer {
    public:
        static void Initialize();
        static void Cleanup();
    private:
        static void CreateInstance();
        static void SetupDebugMessenger();
        static bool HasValidationSupport();
        static std::vector<const char*> GetExtensions();
    };
}