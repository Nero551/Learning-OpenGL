#pragma once
#include "Utilities/Logger.hpp"

/// Non-owning pointer that checks for null dereferences.
/// Does NOT track object lifetime or prevent dangling pointers.
template <typename T> struct CheckedPtr {
    CheckedPtr() = default;

    CheckedPtr(T* objectPtr) {
        ptr = objectPtr;
    }

    CheckedPtr(const std::string_view& nullMessage) {
        this->nullMessage += nullMessage;
    }

    CheckedPtr(T* objectPtr, const std::string_view& nullMessage) {
        ptr = objectPtr;
        this->nullMessage += nullMessage;
    }

    CheckedPtr& operator=(T* objectPtr) {
        ptr = objectPtr;
        return *this;
    }

    T* operator->() const {
        if (!ptr) {
            Logger::Fatal(nullMessage);
        }
        return ptr;
    }

    T& operator*() const {
        return Logger::Require(ptr, nullMessage);
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    void Reset() {
        ptr = nullptr;
    }

    T* Get() const {
        return ptr;
    }

    bool IsNull() const {
        return ptr == nullptr;
    }

private:
    T* ptr = nullptr;
    std::string nullMessage = "[NULL PTR] ";
};
