#pragma once
#include <vector>

#include "Core/OuterCore/Service.hpp"
#include "Utilities/Dirty.hpp"
#include "Utilities/CheckedPtr.hpp"


struct DirtyStore : Service {
    void ClearDirtyObjects() {
        for (auto& dirty : DirtyObjects) {
            dirty->ClearDirty();
        }
    }

private:
    std::vector<CheckedPtr<IDirty>> DirtyObjects = {};
};
