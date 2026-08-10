#include "DirtyManager.hpp"


namespace E {
void DirtyManager::ClearDirtyObjects() {
    for (auto& dirty : DirtyObjects) {
        dirty->ClearDirty();
    }
}

void DirtyManager::RegisterDirty(IDirty* dirty) {
    DirtyObjects.emplace_back(dirty);
}

void DirtyManager::UnRegisterDirty(IDirty* dirty) {
    std::erase(DirtyObjects, dirty);
}

void DirtyManager::EndFrame() {
    ClearDirtyObjects();
}
}
