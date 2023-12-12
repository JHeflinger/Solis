#pragma once
#include <utility>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Solis {
    typedef std::pair<uint32_t, uint32_t> WindowSize;

    class Window {
    public:
        void Initialize();
        void Update();
        void Cleanup();
        void SetName(std::string name) { m_Name = name; }
        void SetDimensions(WindowSize dimensions) { m_Dimensions = dimensions; }
        GLFWwindow* RawWindow() { return m_Window; }
    private:
        std::string m_Name = "Flare";
        GLFWwindow* m_Window;
        WindowSize m_Dimensions = {800, 600};
    };
}