#pragma once
#include "NumberValue.h"

namespace V
{
    class ColorValue : public ValueBase
    {
    public:
        ColorValue(std::string name, int r, int g, int b, float a = 1.f) : m_Name(name), r(r), g(g), b(b), a(a) {};
        std::string GetName() const override { return m_Name; }
        std::tuple<int,int,int,float> GetValue() {return std::make_tuple(r, g, b, a); }
        // setValue by parameter tuple
        void SetValue(std::tuple<int, int, int, float> value) {
            auto [r, g, b, a] = value;
            // check if value is more than 255 or less than 0
            if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0 || a > 1 || a < 0) return;
            // set value
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
    private:
        int r, g, b;
        float a;
        std::string m_Name;
    };
}