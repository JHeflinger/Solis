#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <pthread.h>
#include "Renderer/Renderer.h"
#include "Console/Console.h"
#include "Core/Base.h"

static bool s_RendererStatus = true;
static bool s_ConsoleStatus = true;

void* RunApplication(void* arg) { 
    try {
        Solis::Renderer::Initialize();
        Solis::Renderer::Update();
        Solis::Renderer::Cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        s_RendererStatus = false;
    }
    pthread_exit(NULL);
}

void* RunConsole(void* arg) {
    try {
        Solis::Console::Initialize();
        Solis::Console::Update();
        Solis::Console::Cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        s_ConsoleStatus = false;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t renderer_thread, console_thread;
    int id1, id2;

    pthread_create(&renderer_thread, NULL, RunApplication, &id1);
    pthread_create(&console_thread, NULL, RunConsole, &id2);

    pthread_join(renderer_thread, NULL);
    pthread_join(console_thread, NULL);

    return (s_RendererStatus && s_ConsoleStatus) ? EXIT_SUCCESS : EXIT_FAILURE;
}