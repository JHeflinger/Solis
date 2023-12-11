#pragma once
#include <vulkan/vulkan.h>

namespace Solis {
    class Renderer {
    public:
        static void Initialize();
        static void Cleanup();
    private:
        static void CreateInstance();
        static bool HasValidationSupport();
    };
}