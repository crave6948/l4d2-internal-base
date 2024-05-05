#pragma once
#include "ListValue.h"

namespace V
{
    class StringValue : public ValueBase
    {
        public:
        StringValue(std::string name, std::string value = "") : m_Name(name), m_Value(value) {}
        std::string GetName() const override { return m_Name; }
        std::string GetValue() { return m_Value; }
        void SetValue(std::string value) { m_Value = value; }
        private:
        std::string m_Name;
        std::string m_Value;
    };
} // namespace V