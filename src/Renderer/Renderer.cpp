#include "Renderer.h"
#include "Window.h"
#include <iostream>
#include <cstring>
#include <set>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Solis {

    static VkInstance s_Instance;
    static VkPhysicalDevice s_PhysicalDevice = VK_NULL_HANDLE;
    static VkDebugUtilsMessengerEXT s_DebugMessenger;
    static VkDevice s_Device;
    static VkQueue s_GraphicsQueue;
    static VkSurfaceKHR s_Surface;
    static VkQueue s_PresentQueue;

    static Window s_Window;

    static const std::vector<const char*> s_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    #ifdef NDEBUG
        static const bool s_EnableValidationLayers = false;
    #else
        static const bool s_EnableValidationLayers = true;
    #endif

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {
        std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }

    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, 
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, 
        VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        else
            return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, 
        VkDebugUtilsMessengerEXT debugMessenger, 
        const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }

    static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;
    }

    void Renderer::Initialize() {
        s_Window.Initialize();
        CreateInstance();
        SetupDebugMessenger();
        CreateSurface();
        PickDevice();
        CreateLogicalDevice();
    }

    void Renderer::Update() {
        s_Window.Update();
    }

    void Renderer::Cleanup() {
        s_Window.Cleanup();
        vkDestroyDevice(s_Device, nullptr);
        if (s_EnableValidationLayers)
            DestroyDebugUtilsMessengerEXT(s_Instance, s_DebugMessenger, nullptr);
        vkDestroySurfaceKHR(s_Instance, s_Surface, nullptr);
        vkDestroyInstance(s_Instance, nullptr);
    }

    void Renderer::CreateSurface() {
        if (glfwCreateWindowSurface(s_Instance, s_Window.RawWindow(), nullptr, &s_Surface) != VK_SUCCESS)
            throw std::runtime_error("Failed to create window surface!");
    }

    void Renderer::CreateInstance() {
        // Check for validation layers
        if (s_EnableValidationLayers && !HasValidationSupport())
            throw std::runtime_error("Validation layers requested, but not available!");

        // Creating application info
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Solis Renderer";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Creating instance info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        auto extensions = GetExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (s_EnableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(s_ValidationLayers.size());
            createInfo.ppEnabledLayerNames = s_ValidationLayers.data();
            PopulateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &s_Instance) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan Instance!");
    }

    void Renderer::SetupDebugMessenger() {
        if (!s_EnableValidationLayers) return;
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        PopulateDebugMessengerCreateInfo(createInfo);
        if (CreateDebugUtilsMessengerEXT(s_Instance, &createInfo, nullptr, &s_DebugMessenger) != VK_SUCCESS)
            throw std::runtime_error("Failed to set up debug messenger!");
    }

    void Renderer::PickDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(s_Instance, &deviceCount, nullptr);
        if (deviceCount == 0) 
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(s_Instance, &deviceCount, devices.data());
        for (const auto& device : devices) {
            if (SuitableDevice(device)) {
                s_PhysicalDevice = device;
                break;
            }
        }
        if (s_PhysicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("Failed to find a suitable GPU!");
    }

    void Renderer::CreateLogicalDevice() {
        QueueFamily indices = FindQueueFamilies(s_PhysicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };
        
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = 0;
        if (s_EnableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(s_ValidationLayers.size());
            createInfo.ppEnabledLayerNames = s_ValidationLayers.data();
        } else createInfo.enabledLayerCount = 0;
        if (vkCreateDevice(s_PhysicalDevice, &createInfo, nullptr, &s_Device) != VK_SUCCESS)
            throw std::runtime_error("Failed to create logical device!");
        vkGetDeviceQueue(s_Device, indices.PresentFamily.value(), 0, &s_PresentQueue);
        vkGetDeviceQueue(s_Device, indices.GraphicsFamily.value(), 0, &s_GraphicsQueue);
    }

    bool Renderer::HasValidationSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        
        for (const char* layerName : s_ValidationLayers) {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers) {
                if (std::strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound) return false;
        }
        return true;
    }

    QueueFamily Renderer::FindQueueFamilies(VkPhysicalDevice device) {
        QueueFamily indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.GraphicsFamily = i;
                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, s_Surface, &presentSupport);
                if (presentSupport)
                    indices.PresentFamily = i;
            }
            i++;
        }
        return indices;
    }

    bool Renderer::SuitableDevice(VkPhysicalDevice device) {
        //NOTE: modify as needed for certain GPU features
        QueueFamily indices = Renderer::FindQueueFamilies(device);
        return indices.IsComplete();
    }

    std::vector<const char*> Renderer::GetExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if (s_EnableValidationLayers) 
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        return extensions;
    }

}