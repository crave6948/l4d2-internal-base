#include "EntityCache.h"

namespace Utils
{
    void Utils::EntityCache::update()
    {
        // clear the cache
        m_EntityCache[EClientClass::Infected].clear();
        m_EntityCache[EClientClass::Boomer].clear();
        m_EntityCache[EClientClass::Jockey].clear();
        m_EntityCache[EClientClass::Smoker].clear();
        m_EntityCache[EClientClass::Hunter].clear();
        m_EntityCache[EClientClass::Spitter].clear();
        m_EntityCache[EClientClass::Charger].clear();
        m_EntityCache[EClientClass::Witch].clear();
        m_EntityCache[EClientClass::Tank].clear();
        // local player index
        const int nLocalIndex = I::EngineClient->GetLocalPlayer();
        for (int n = 1; n <= I::ClientEntityList->GetMaxEntities() + 1; n++)
        {
            if (n == nLocalIndex)
                continue;
            // get the entity of index n
            IClientEntity *pEntity = I::ClientEntityList->GetClientEntity(n);
            // check if entity is valid
            if (!pEntity)
                continue;
            ClientClass *pClass = pEntity->GetClientClass();
            if (!pClass)
                continue;
            // using switch case to check if entity is a zombie and alive
            switch (pClass->m_ClassID)
            {
            case EClientClass::Witch:
            case EClientClass::Infected:
            {
                C_Infected *pBaseEntity = pEntity->As<C_Infected *>();
                if (!G::Util.IsInfectedAlive(pBaseEntity->m_usSolidFlags(), pBaseEntity->m_nSequence()))
                    continue;
                m_EntityCache[pClass->m_ClassID].push_back(pEntity);
                break;
            }
            case EClientClass::Tank:
            case EClientClass::Boomer:
            case EClientClass::Jockey:
            case EClientClass::Smoker:
            case EClientClass::Hunter:
            case EClientClass::Spitter:
            case EClientClass::Charger:
            {
                C_TerrorPlayer *pBaseEntity = pEntity->As<C_TerrorPlayer *>();
                if (pBaseEntity->deadflag())
                    continue;
                m_EntityCache[pClass->m_ClassID].push_back(pEntity);
                break;
            }
            }
        }
    }
    std::vector<IClientEntity *> EntityCache::getEntityFromGroup(int group)
    {
        return m_EntityCache[group];
    }
}