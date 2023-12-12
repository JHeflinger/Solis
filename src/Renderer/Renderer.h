#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <optional>

namespace Solis {
    struct QueueFamily {
        std::optional<uint32_t> GraphicsFamily;
        bool IsComplete() { return GraphicsFamily.has_value(); }
    };

    class Renderer {
    public:
        static void Initialize();
        static void Cleanup();
    private:
        static void CreateInstance();
        static void SetupDebugMessenger();
        static void PickDevice();
        static bool HasValidationSupport();
        static bool SuitableDevice(VkPhysicalDevice device);
        static QueueFamily FindQueueFamilies(VkPhysicalDevice device);
        static std::vector<const char*> GetExtensions();
    };
}