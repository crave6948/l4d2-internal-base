#pragma once
#include <vector>
#include <string>
#include "Values/StringValue.h"

namespace V
{
    class ValueManager
    {
    public:
        ValueManager();

        void AddValue(ValueBase *value);

        ValueBase *GetValue(std::string name);

        std::vector<ValueBase *> GetValues();
    private:
        std::vector<ValueBase *> m_Values;
    };
}