#pragma once

#include <utility>

#include "IDirty.hpp"
#include "Core/OuterCore/ServiceStore.hpp"
#include "Core/Services/DirtyStore.hpp"

template <typename T> struct Dirty : IDirty {
    Dirty() {
        ServiceStore::Ins->Get<DirtyStore>().RegisterDirty(this);
        DirtyFlag = true;
    }

    Dirty(const T& value) : Value(value) {
        ServiceStore::Ins->Get<DirtyStore>().RegisterDirty(this);
        DirtyFlag = true;
    }


    void Set(const T& value) {
        if (Value != value) {
            Value = value;
            DirtyFlag = true;
        }
    }

    void Set(T&& value) {
        if (Value != value) {
            Value = std::move(value);
            DirtyFlag = true;
        }
    }

    [[nodiscard]] bool IsDirty() const {
        return DirtyFlag;
    }

    void ClearDirty() override {
        DirtyFlag = false;
    }

    operator const T&() const {
        return Value;
    }

    const T& Get() const {
        return Value;
    }

    T& Get() {
        DirtyFlag = true;
        return Value;
    }

    T* operator->() {
        DirtyFlag = true;
        return &Value;
    }

    const T* operator->() const {
        return &Value;
    }

    Dirty& operator=(const Dirty& rhs) {
        Set(rhs.Value);
        return *this;
    }

    Dirty& operator=(Dirty&& rhs) {
        Set(std::move(rhs.Value));
        return *this;
    }

    Dirty& operator=(const T& value) {
        Set(value);
        return *this;
    }

    Dirty& operator=(T&& value) {
        Set(std::move(value));
        return *this;
    }

    Dirty& operator+=(const Dirty& rhs) {
        Set(Value + rhs.Value);
        return *this;
    }

    Dirty& operator-=(const Dirty& rhs) {
        Set(Value - rhs.Value);
        return *this;
    }

    Dirty& operator*=(const Dirty& rhs) {
        Set(Value * rhs.Value);
        return *this;
    }

    Dirty& operator/=(const Dirty& rhs) {
        Set(Value / rhs.Value);
        return *this;
    }

    Dirty& operator+=(const T& rhs) {
        Set(Value + rhs);
        return *this;
    }

    Dirty& operator-=(const T& rhs) {
        Set(Value - rhs);
        return *this;
    }

    Dirty& operator*=(const T& rhs) {
        Set(Value * rhs);
        return *this;
    }

    Dirty& operator/=(const T& rhs) {
        Set(Value / rhs);
        return *this;
    }

    bool operator==(const Dirty& rhs) const {
        return Value == rhs.Value;
    }

    bool operator!=(const Dirty& rhs) const {
        return Value != rhs.Value;
    }

    bool operator<(const Dirty& rhs) const {
        return Value < rhs.Value;
    }

    bool operator<=(const Dirty& rhs) const {
        return Value <= rhs.Value;
    }

    bool operator>(const Dirty& rhs) const {
        return Value > rhs.Value;
    }

    bool operator>=(const Dirty& rhs) const {
        return Value >= rhs.Value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Dirty& dirty) {
        return os << dirty.Value;
    }

private:
    T Value{};
    bool DirtyFlag = false;
};
