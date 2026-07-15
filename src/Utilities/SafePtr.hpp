#pragma once
#include <string>
#include "Utilities/Services/LoggerService.hpp"

template <typename T> struct SafePtr
{
    SafePtr() = default;

    ~SafePtr()
    {
        Reset();
        delete ptr;
    }

    SafePtr(const std::string_view& nullMessage) { this->nullMessage += nullMessage; }

    SafePtr& operator=(T* objectPtr)
    {
        ptr = objectPtr;
        return *this;
    }

    T* operator->() const
    {
        if (!ptr) { LoggerService::Fatal(nullMessage); }
        return ptr;
    }

    T& operator*() { return LoggerService::Require(ptr, nullMessage); }

    operator bool() const { return ptr != nullptr; }

    void Reset() { ptr = nullptr; }

    T* Get() const { return ptr; }

private:
    T* ptr = nullptr;
    std::string nullMessage = "[NULL PTR] ";
};
