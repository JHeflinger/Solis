#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <optional>

namespace Solis {
    struct QueueFamily {
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> PresentFamily;
        bool IsComplete() { return GraphicsFamily.has_value() && PresentFamily.has_value(); }
    };

    class Renderer {
    public:
        static void Initialize();
        static void Update();
        static void Cleanup();
    private:
        static void CreateSurface();
        static void CreateInstance();
        static void SetupDebugMessenger();
        static void PickDevice();
        static void CreateLogicalDevice();
        static bool HasValidationSupport();
        static bool SuitableDevice(VkPhysicalDevice device);
        static QueueFamily FindQueueFamilies(VkPhysicalDevice device);
        static std::vector<const char*> GetExtensions();
    };
}