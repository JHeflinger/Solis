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
        static void DrawFrame();
        static void Wait();
        static void Cleanup();
    private:
        static void SetResizeCallback();
        static void CleanSwapChain();
        static void RecreateSwapChain();
        static void CreateSyncObjects();
        static void CreateCommandBuffer();
        static void CreateCommandPool();
        static void CreateFrameBuffers();
        static void CreateRenderPass();
        static void CreateGraphicsPipeline();
        static void CreateImageViews();
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
        static VkShaderModule CreateShaderModule(const std::vector<char>& code);
        static void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    };
}