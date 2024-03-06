#pragma once
#include "BooleanValue.h"
namespace V
{
    class NumberValue : public ValueBase
    {
    public:
    NumberValue(std::string name, int value = 0, int min = 0, int max = 100) : m_Name(name), m_Value(value), m_Min(min), m_Max(max) {}
    std::string GetName() const override { return m_Name; }
    int GetValue() { return m_Value; }
    void SetValue(int value) { m_Value = value; }
    int GetMin() { return m_Min; }
    int GetMax() { return m_Max; }
    private:
    std::string m_Name;
    int m_Value;
    int m_Min;
    int m_Max;
    };
} // namespace V
