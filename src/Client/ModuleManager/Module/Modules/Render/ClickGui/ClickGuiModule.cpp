#include "ClickGuiModule.h"

// access None.h for Menu.h
#include "../../../../../None.h"

namespace Client::Module::ClickGuiModule
{
    void ClickGui::onEnabled()
    {
        Client::client.menu.toggle();
        this->setEnabled(false);
    }
}