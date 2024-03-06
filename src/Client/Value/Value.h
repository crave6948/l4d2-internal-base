#pragma once
#include <string>

namespace V
{
    class ValueBase
    {
    public:
        //deconstructor
        virtual ~ValueBase() {}
        //virtual getName function
        virtual std::string GetName() const = 0;
    };
}
