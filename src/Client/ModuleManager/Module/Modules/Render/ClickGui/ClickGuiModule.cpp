#include "ClickGuiModule.h"

// access None.h for Menu.h
#include "../../../../../None.h"

namespace Client::Module::ClickGuiModule
{
    void ClickGui::onEnabled()
    {
        this->setEnabled(false);
    }
}