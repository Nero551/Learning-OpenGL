#pragma once

#include <iostream>

struct LoggerService {
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

private:
  static constexpr auto Reset = "\033[0m";
  static constexpr auto Red = "\033[31m";
  static constexpr auto Green = "\033[32m";
  static constexpr auto Yellow = "\033[33m";
  static constexpr auto Blue = "\033[34m";
};