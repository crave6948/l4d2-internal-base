#pragma once
#include "ColorValue.h"
namespace V
{
    class Range
    {
    private:
        float min;
        float max;

    public:
        Range(float min = 0.f, float max = 0.f) : min(min), max(max){};
        float GetMin() { return min; }
        float GetMax() { return max; }
        void SetMin(float min)
        {
            if (min > max)
                return;
            this->min = min;
        }
        void SetMax(float max)
        {
            if (max < min)
                return;
            this->max = max;
        }
    };
    class FloatRangeValue : public ValueBase
    {
    public:
        FloatRangeValue(std::string name, Range value, Range maximumRange, std::string format = "None") : m_Name(name), m_Value(value), m_MaximumRange(maximumRange), m_format(format) {}
        std::string GetName() const override { return m_Name; }
        std::pair<float, float> GetValue() { return std::make_pair(m_Value.GetMin(), m_Value.GetMax()); }
        void SetValue(float value_min, float value_max)
        {
            // if value_min is lower than maximum min value set it to maximum min value
            if (value_min < m_MaximumRange.GetMin())
                value_min = m_MaximumRange.GetMin();
            // if value_max is higher than maximum max value set it to maximum max value
            if (value_max > m_MaximumRange.GetMax())
                value_max = m_MaximumRange.GetMax();
            m_Value.SetMin(value_min);
            m_Value.SetMax(value_max);
        }
        std::pair<float, float> GetMaximumRange() { return std::make_pair(m_MaximumRange.GetMin(), m_MaximumRange.GetMax()); }
        std::string GetFormat() { return m_format; }

    private:
        std::string m_Name;
        Range m_Value;
        Range m_MaximumRange;
        std::string m_format;
    };
} // namespace V
