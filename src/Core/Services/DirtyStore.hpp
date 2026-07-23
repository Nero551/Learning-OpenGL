#pragma once
#include <vector>

#include "Core/OuterCore/Service.hpp"
#include "Utilities/IDirty.hpp"
#include "Utilities/CheckedPtr.hpp"


struct DirtyStore : Service {
    void ClearDirtyObjects() {
        for (auto& dirty : DirtyObjects) {
            dirty->ClearDirty();
        }
    }

    void RegisterDirty(IDirty* dirty) {
        DirtyObjects.emplace_back(dirty);
    }

private:
    std::vector<CheckedPtr<IDirty>> DirtyObjects = {};
};
