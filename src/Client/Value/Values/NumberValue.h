#pragma once
#include "BooleanValue.h"
namespace V
{
    class NumberValue : public ValueBase
    {
    public:
        NumberValue(std::string name, int value = 0, int min = 0, int max = 100, std::string format = "None") : m_Name(name), m_Value(value), m_Min(min), m_Max(max), m_format(format) {}
        std::string GetName() const override { return m_Name; }
        int GetValue() { return m_Value; }
        void SetValue(int value)
        {
            if (value < m_Min)
                m_Value = m_Min;
            else if (value > m_Max)
                m_Value = m_Max;
            else
            m_Value = value;
        }
        int GetMin() { return m_Min; }
        int GetMax() { return m_Max; }
        std::string GetFormat() { return m_format; }
    private:
        std::string m_Name;
        int m_Value;
        int m_Min;
        int m_Max;
        std::string m_format;
    };
} // namespace V
