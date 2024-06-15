#pragma once
#include "../../../../../SDK/SDK.h"

namespace Utils
{
    class EntityCache {
        public:
        void update();
        std::vector<IClientEntity *> getEntityFromGroup(int group);
        private:
        std::map<int, std::vector<IClientEntity*>> m_EntityCache;
    };
    inline EntityCache g_EntityCache = EntityCache();
}