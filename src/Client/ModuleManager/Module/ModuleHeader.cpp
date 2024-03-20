#include "ModuleHeader.h"
#include "../../None.h"
namespace Client::Module
{
    void Module::toggle()
    {
        setEnabled(!state);
    }
}