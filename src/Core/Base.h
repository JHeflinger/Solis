#include <stdexcept>
#include <iostream>
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

#define INFO(trace)  std::cout << GREEN << "INFO: " << RESET << trace << std::endl
#define ERROR(trace) throw std::runtime_error((std::string(RED) + "ERROR: " + std::string(RESET) + std::string(trace)).c_str())
#define WARN(trace)  std::cout << YELLOW << "WARNING: " << RESET << trace << std::endl