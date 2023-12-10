#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <utility>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Flare {
public:
    void Run() {
        InitWindow();
        InitVulkan();
        MainLoop();
        Cleanup();
    }

private:
    void InitWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_Window = glfwCreateWindow(m_WindowDimensions.first, m_WindowDimensions.second, "Flare", nullptr, nullptr);

    }

    void InitVulkan() {

    }

    void MainLoop() {
        while (!glfwWindowShouldClose(m_Window)) {
            glfwPollEvents();
        }
    }

    void Cleanup() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
private:
    GLFWwindow* m_Window;
    std::pair<uint32_t, uint32_t> m_WindowDimensions = {800, 600};
};

int main() {
    Flare app;

    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}