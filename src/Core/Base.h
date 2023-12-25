#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

#define APPVERSION "v0.0.1"

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define PURPLE "\033[35m"

static std::vector<std::string> s_LogQueue;

#define INFO(trace)  std::cout << GREEN << "[INFO] " << RESET << trace << std::endl
#define ERROR(trace)  std::cout << RED << "[ERROR] " << RESET << trace << std::endl
#define FATAL(trace) throw std::runtime_error((std::string(RED) + "[FATAL] " + std::string(RESET) + std::string(trace)).c_str())
#define WARN(trace)  std::cout << YELLOW << "[WARNING] " << RESET << trace << std::endl
#define DEBUG(trace) std::cout << PURPLE << "[DEBUG] " << RESET << trace << std::endl
#define ABNORMAL(label) std::string(std::string(BLUE) + std::string(label) + std::string(RESET))
#define FLUSH() while (s_LogQueue.size() > 0) { std::string log = s_LogQueue[0]; s_LogQueue.erase(s_LogQueue.begin()); std::cout << log << std::endl; }