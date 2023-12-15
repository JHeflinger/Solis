#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <array>

namespace Solis {
    struct Vertex {
        glm::vec2 Position;
        glm::vec3 Color;

        static VkVertexInputBindingDescription GetBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescription{};
            attributeDescription[0].binding = 0;
            attributeDescription[0].location = 0;
            attributeDescription[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescription[0].offset = offsetof(Vertex, Position);
            attributeDescription[1].binding = 0;
            attributeDescription[1].location = 1;
            attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescription[1].offset = offsetof(Vertex, Color);
            return attributeDescription;
        }
    };

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
        static void CreateVertexBuffer();
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
        static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
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