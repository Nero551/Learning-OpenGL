#pragma once

struct Module {
    virtual void Start() {
    }

    virtual void Update(double dt) {
    }

    virtual void Stop() {
    }

    virtual void Render() {
    }

    virtual ~Module() {
    }

    Module() = default;

    Module(const Module &) = delete;

    Module &operator=(const Module &) = delete;

    Module(Module &&) = default;

    Module &operator=(Module &&) = default;
};