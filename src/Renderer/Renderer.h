#pragma once
#include "Structures.h"
#include <vector>
#include <iostream>
#include <array>

namespace Solis {
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
        static void CreateColorResources();
        static VkSampleCountFlagBits GetMaxUsableSampleCount();
        static void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
        static bool HasStencilComponent(VkFormat format);
        static VkFormat FindDepthFormat();
        static VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        static VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        static void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        static void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
        static VkCommandBuffer BeginSingleTimeCommands();
        static void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
        static void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
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