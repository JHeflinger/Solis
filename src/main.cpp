#include <iostream>
#include <stdexcept>
#include <cstdlib>
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
        Solis::Renderer::Initialize();
    }

    void Update() {
        Solis::Renderer::Update();
    }

    void Cleanup() {
        Solis::Renderer::Cleanup();
    }
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