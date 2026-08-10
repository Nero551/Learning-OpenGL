#pragma once
#include "Core/OuterCore/Service.hpp"
#include "Core/OuterCore/DirtySystem/IDirty.hpp"


namespace E {
struct DirtyManager : Service {
    void ClearDirtyObjects();

    void RegisterDirty(IDirty* dirty);

    void UnRegisterDirty(IDirty* dirty);

private:
    std::vector<IDirty*> DirtyObjects = {};

protected:
    void EndFrame() override;
};
}
