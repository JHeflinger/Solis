#pragma once
#include <string>

namespace Solis {
    enum class Command {
        HELP,
        VERSION,
        INVALID
    };

    class Console {
    public:
        static void Initialize();
        static void Update();
        static void Cleanup();
    private:
        static void HelpTrace(std::string command);
        static Command GetCommand(std::string commandstr);
        static void InitializeCommands();
        static std::string Input();
    };
}