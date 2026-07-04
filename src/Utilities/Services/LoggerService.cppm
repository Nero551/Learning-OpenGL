module;
#include <iostream>

export module LoggerService;

export struct LoggerService {
  static constexpr const char *Reset = "\033[0m";
  static constexpr const char *Red = "\033[31m";
  static constexpr const char *Yellow = "\033[33m";
  static constexpr const char *Green = "\033[32m";
  static constexpr const char *Blue = "\033[34m";

  template <typename T> static void Print(const T &message) { std::cout << Blue << message << "\n"; }

  template <typename T> static void Info(const T &message) {
    std::cout << Green << "[INFO] " << Reset << message << "\n";
  }
  template <typename T> static void Warning(const T &message) {
    std::cout << Yellow << "[WARNING] " << Reset << message << "\n";
  }
  template <typename T> static void Error(const T &message) {
    std::cerr << Red << "[ERROR] " << Reset << message << "\n";
  }
};