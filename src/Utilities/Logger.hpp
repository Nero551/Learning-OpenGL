#pragma once


struct Logger {
    template <typename T> static void Print(const T& message) { std::cout << message << "\n"; }

    template <typename T> static void Info(const T& message) {
        std::cout << Green << "[INFO] " << Reset << message << "\n";
    }

    template <typename T> static void Warning(const T& message) {
        std::cout << Yellow << "[WARNING] " << Reset << message << "\n";
    }

    template <typename T> static void Error(const T& message) {
        std::cerr << Red << "[ERROR] " << Reset << message << "\n";
    }


    template <typename T> [[noreturn]] static void Fatal(const T& message) {
        std::cerr << Red << "[FATAL] " << Reset << message << '\n';
        throw std::runtime_error("");
    }

    template <typename T> static T& Require(T* rawPtr, const std::string& message) {
        if (!rawPtr) { Logger::Fatal(message); }
        return *rawPtr;
    }

private:
    static constexpr auto Reset = "\033[0m";
    static constexpr auto Red = "\033[31m";
    static constexpr auto Green = "\033[32m";
    static constexpr auto Yellow = "\033[33m";
    static constexpr auto Blue = "\033[34m";
};
