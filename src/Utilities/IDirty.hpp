#pragma once

struct IDirty {
    virtual void ClearDirty() {}
    virtual ~IDirty() = default;
};
