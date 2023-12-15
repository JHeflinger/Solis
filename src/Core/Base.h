#include <stdexcept>
#include <iostream>
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

#define INFO(trace)  std::cout << GREEN << trace << RESET << std::endl
#define ERROR(trace) throw std::runtime_error((std::string(RED) + std::string(trace) + std::string(RESET)).c_str())
#define WARN(trace)  std::cout << YELLOW << trace << RESET << std::endl