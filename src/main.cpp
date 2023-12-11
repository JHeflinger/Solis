#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "Renderer/Window.h"
#include "Renderer/Renderer.h"

class Flare {
public:
    void Run() {
        Init();
        Update();
        Cleanup();
    }

private:
    void Init() {
        m_Window.Initialize();
        Solis::Renderer::Initialize();
    }

    void Update() {
        m_Window.Update();
    }

    void Cleanup() {
        m_Window.Cleanup();
        Solis::Renderer::Cleanup();
    }
private:
    Solis::Window m_Window;
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