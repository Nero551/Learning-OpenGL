#pragma once
#include "EventBus.hpp"
#include "Utilities/SafePtr.hpp"

struct Services {
    static SafePtr<Services> Ins;
    EventBus EventBus;
};
