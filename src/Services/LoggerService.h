#pragma once

#include <iostream>
namespace ConsoleColors {
constexpr const char *Reset = "\033[0m";
constexpr const char *Red = "\033[31m";
constexpr const char *Yellow = "\033[33m";
constexpr const char *Green = "\033[32m";
constexpr const char *Blue = "\033[34m";
} // namespace ConsoleColors

struct LoggerService {

  template <typename T> static void Print(const T &message) { std::cout << ConsoleColors::Blue << message << "\n"; }

  template <typename T> static void Info(const T &message) {
    std::cout << ConsoleColors::Green << "[INFO] " << ConsoleColors::Reset << message << "\n";
  }
  template <typename T> static void Warning(const T &message) {
    std::cout << ConsoleColors::Yellow << "[WARNING] " << ConsoleColors::Reset << message << "\n";
  }
  template <typename T> static void Error(const T &message) {
    std::cerr << ConsoleColors::Red << "[ERROR] " << ConsoleColors::Reset << message << "\n";
  }
};
