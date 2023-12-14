#include "Window.h"
#include "Renderer.h"

namespace Solis {

    void Window::Initialize() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_Window = glfwCreateWindow(m_Dimensions.first, m_Dimensions.second, m_Name.c_str(), nullptr, nullptr);
    }

    void Window::Update() {
        while (!glfwWindowShouldClose(m_Window)) {
            glfwPollEvents();
            Renderer::DrawFrame();
        }
    }

    void Window::Cleanup() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

}