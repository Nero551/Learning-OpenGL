#pragma once

namespace E {
    struct IDirty {
        virtual void ClearDirty() {}
        virtual ~IDirty() = default;
    };
}
