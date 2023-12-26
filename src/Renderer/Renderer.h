#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <array>

namespace Solis {
    struct UniformBufferObject {
        glm::mat4 Model;
        glm::mat4 View;
        glm::mat4 Projection;
    };

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 TextureCoord;

        static VkVertexInputBindingDescription GetBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescription{};
            attributeDescription[0].binding = 0;
            attributeDescription[0].location = 0;
            attributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescription[0].offset = offsetof(Vertex, Position);

            attributeDescription[1].binding = 0;
            attributeDescription[1].location = 1;
            attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescription[1].offset = offsetof(Vertex, Color);

            attributeDescription[2].binding = 0;
            attributeDescription[2].location = 2;
            attributeDescription[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescription[2].offset = offsetof(Vertex, TextureCoord);

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
        static void LoadModel();
        static void CreateDepthResources();
        static void CreateTextureSampler();
        static void CreateTextureImageView();
        static void CreateTextureImage();
        static void CreateDescriptorSets();
        static void CreateDescriptorPool();
        static void CreateUniformBuffers();
        static void CreateDescriptorSetLayout();
        static void CreateIndexBuffer();
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
        static bool HasStencilComponent(VkFormat format);
        static VkFormat FindDepthFormat();
        static VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        static VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
        static void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        static void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        static VkCommandBuffer BeginSingleTimeCommands();
        static void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
        static void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        static void UpdateUniformBuffer(uint32_t currentImage);
        static void CopyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
        static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
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