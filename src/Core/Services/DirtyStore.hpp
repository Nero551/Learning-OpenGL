#pragma once
#include "Core/OuterCore/Service.hpp"
#include "Core/OuterCore/DirtySystem/IDirty.hpp"
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

    void UnRegisterDirty(IDirty* dirty) {
        std::erase(DirtyObjects, dirty);
    }

private:
    std::vector<IDirty*> DirtyObjects = {};
};
