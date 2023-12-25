#include "Console.h"
#include "../Core/Base.h"
#include <map>

#define BUFFERSIZE 1024

namespace Solis {

    static char s_CommandBuffer[1024];
    static bool s_Listen = true;
    static std::map<std::string, Command> s_Commands;

    void Console::Initialize() {
        InitializeCommands();
    }
    
    void Console::Update() {
        while (s_Listen) {
            //FLUSH();
            std::string input = Input();
            switch (GetCommand(input)) {
                case Command::INVALID:
                    ERROR("Invalid command!");
                    break;
                case Command::HELP:
                    HelpTrace(input);
                    break;
                case Command::VERSION:
                    std::cout << ABNORMAL("Version: ") << APPVERSION << std::endl;
                    break;
                default:
                    FATAL("Error duing command fetch");
            }
            break; // temp, delete later so we continue
        }
    }

    void Console::Cleanup() {
        INFO("Shutting down user console...");
    }

    void Console::HelpTrace(std::string command) {
        std::cout << "\n" << std::endl;

        std::cout << "Usage:" << std::endl;
        std::cout << "   [COMMAND] [FLAGS...] [ARGS...]" << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << "Information" << std::endl;
        std::cout << "   h, help                        lists all available commands" << std::endl;
        std::cout << "   h, help              <arg>     provides a detailed description for a command" << std::endl;
        std::cout << "   v, version                     prints out application version" << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << "Scene" << std::endl;
        std::cout << "   i, import    <flags> <arg>     imports a scene configuration file" << std::endl;
        std::cout << "   e, export            <arg>     exports the current scene to a location" << std::endl;
        std::cout << "   n, new                         resets the current scene" << std::endl;
        
        std::cout << "\n" << std::endl;
    }
    
    Command Console::GetCommand(std::string commandstr) {
        if (s_Commands.find(commandstr) == s_Commands.end())
            return Command::INVALID;
        else return s_Commands[commandstr];
    }

    void Console::InitializeCommands() {
        s_Commands["h"] = Command::HELP;
        s_Commands["help"] = Command::HELP;
        s_Commands["v"] = Command::VERSION;
        s_Commands["version"] = Command::VERSION;
    }

    std::string Console::Input() {
        std::cout << ">> ";
        char buffer[1024];
        std::cin >> buffer;
        return std::string(buffer);
    }

}