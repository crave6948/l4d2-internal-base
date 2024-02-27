// interihance from Value.h
#include <string>
#include "../Value.h"
namespace V
{
    class BooleanValue : public ValueBase
    {
        public:
        BooleanValue(std::string name, bool value = false) : m_Name(name), m_Value(value) {}
        std::string GetName() const override { return m_Name; }
        bool GetValue() { return m_Value; }
        void setValue(bool value) { m_Value = value; }
        private:
        std::string m_Name;
        bool m_Value;
    };
} // namespace V
