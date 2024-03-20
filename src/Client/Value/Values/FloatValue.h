#pragma once
#include "NumberValue.h"
namespace V
{
    class FloatValue : public ValueBase
    {
    public:
        FloatValue(std::string name, float value = 0.f, float min = 0.f, float max = 100.f, std::string format = "None") : m_Name(name), m_Value(value), m_Min(min), m_Max(max), m_format(format) {}
        std::string GetName() const override { return m_Name; }
        float GetValue() { return m_Value; }
        void SetValue(float value)
        {
            if (value < m_Min)
                m_Value = m_Min;
            else if (value > m_Max)
                m_Value = m_Max;
            else
            m_Value = value;
        }
        float GetMin() { return m_Min; }
        float GetMax() { return m_Max; }
        std::string GetFormat() { return m_format; }
    private:
        std::string m_Name;
        float m_Value;
        float m_Min;
        float m_Max;
        std::string m_format;
    };
} // namespace V
