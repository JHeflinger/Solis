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

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR Capabilities;
        std::vector<VkSurfaceFormatKHR> Formats;
        std::vector<VkPresentModeKHR> PresentModes;
    };

    class Renderer {
    public:
        static void Initialize();
        static void Update();
        static void Cleanup();
    private:
        static void CreateSwapChain();
        static void CreateSurface();
        static void CreateInstance();
        static void SetupDebugMessenger();
        static void PickDevice();
        static void CreateLogicalDevice();
        static bool HasValidationSupport();
        static bool SuitableDevice(VkPhysicalDevice device);
        static bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        static QueueFamily FindQueueFamilies(VkPhysicalDevice device);
        static std::vector<const char*> GetExtensions();
        static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
        static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    };
}