#pragma once
#include "NumberValue.h"
#include <vector>
namespace V
{
    class ListValue : public ValueBase
    {
    public:
        ListValue(std::string name, std::vector<std::string> lists, std::string selected = "") : m_Name(name), m_Lists(lists), m_Selected(selected) {}
        std::string GetName() const override { return m_Name; }
        std::string GetSelected() { return m_Selected; }
        void setSelected(std::string selected) { m_Selected = selected; }
        std::vector<std::string> GetLists() { return m_Lists; }

    private:
        std::string m_Name;
        std::string m_Selected;
        std::vector<std::string> m_Lists;
    };
}