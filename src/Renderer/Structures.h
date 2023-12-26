#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <optional>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

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

        bool operator==(const Vertex& other) const {
            return Position == other.Position && Color == other.Color && TextureCoord == other.TextureCoord;
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
}

namespace std {
    template<> struct hash<Solis::Vertex> {
        size_t operator() (Solis::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.Position) ^
                    (hash<glm::vec3>()(vertex.Color) << 1)) >> 1) ^
                    (hash<glm::vec2>()(vertex.TextureCoord) << 1);
        }
    };
}