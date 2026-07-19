#pragma once

template <typename T> struct Dirty {
    Dirty(T& value) : Value(value) {}

    void Set(const T& value) {
        if (Value != value) {
            Value = value;
            DirtyFlag = true;
        }
    }

    T& Get() {
        return Value;
    }

    bool IsDirty() {
        return DirtyFlag;
    }

    void ClearDirty() {
        DirtyFlag = false;
    }

    explicit operator T&() {
        return Value;
    }

    Dirty& operator=(const T& value) {
        Set(value);
        return *this;
    }

private:
    T Value = {};
    bool DirtyFlag = false;
};
