#pragma once
#include "IDirty.hpp"

template <typename T> struct Dirty : IDirty {
    Dirty(T value) : Value(value) {}

    void Set(const T& value) {
        if (Value != value) {
            Value = value;
            DirtyFlag = true;
        }
    }

    T* operator->() {
        return &Get();
    }


    bool IsDirty() {
        return DirtyFlag;
    }

    void ClearDirty() override {
        DirtyFlag = false;
    }

    operator const T&() const {
        return Value;
    }

    Dirty& operator=(const Dirty& dirty) {
        Set(dirty.Value);
        return *this;
    }

    Dirty& operator=(const T& value) {
        Set(value);
        return *this;
    }

    Dirty operator+(const Dirty& dirty) {
        Set(Value + dirty.Value);
        return *this;
    }

    Dirty operator-(const Dirty& dirty) {
        Set(Value - dirty.Value);
        return *this;
    }

    Dirty operator*(const Dirty& dirty) {
        Set(Value * dirty.Value);
        return *this;
    }

    Dirty operator/(const Dirty& dirty) {
        Set(Value / dirty.Value);
        return *this;
    }

    Dirty& operator+=(const Dirty& dirty) {
        Value = Value + dirty.Value;
        return *this;
    }

    Dirty& operator-=(const Dirty& dirty) {
        Value = Value - dirty.Value;
        return *this;
    }

    Dirty& operator*=(const Dirty& dirty) {
        Value = Value * dirty.Value;
        return *this;
    }

    Dirty& operator/=(const Dirty& dirty) {
        Value = Value / dirty.Value;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Dirty& dirty) {
        return os << dirty.Value;
    }

private:
    T Value = {};
    bool DirtyFlag = false;

    T& Get() {
        DirtyFlag = true;
        return Value;
    }
};
