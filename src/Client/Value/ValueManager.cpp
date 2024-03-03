#include "ValueManager.h"
namespace V
{
    ValueManager::ValueManager()
    {
    }
    void ValueManager::AddValue(ValueBase *value)
    {
        m_Values.push_back(value);
    }
    ValueBase *ValueManager::GetValue(std::string name)
    {
        for (auto value : m_Values)
        {
            if (value->GetName() == name)
            {
                return value;
            }
        }
        return nullptr;
    }
    std::vector<ValueBase *> ValueManager::GetValues()
    {
        return m_Values;
    }
}