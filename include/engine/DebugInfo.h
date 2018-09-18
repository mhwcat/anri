#ifndef ANRI_DEBUGINFO_H
#define ANRI_DEBUGINFO_H

#include <engine/math/Vec2.h>

struct DebugInfo {
    public:
        float renderTime;
        float updateTime;
        float memoryUsageBytes;
        Vec2f playerPosition;
        Vec2f playerVelocity;

        static DebugInfo& getInstance()
        {
            static DebugInfo instance;

            return instance;
        }
        DebugInfo(DebugInfo const&) = delete;
        DebugInfo(DebugInfo&&) = delete;

    private:
        DebugInfo() = default;
};

#endif //ANRI_DEBUGINFO_H
