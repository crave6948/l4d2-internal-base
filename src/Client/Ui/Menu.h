#pragma once
#include "../../SDK/SDK.h"
#include "components/CategoryUI.h"

namespace Client::Menu
{
    class Menu
    {
    public:
        void init();
        void toggle()
        {
            toggled = !toggled;
            toggled ? onEnabled() : onDisabled();
        }
        void onEnabled();
        void onDisabled();

        void drawScreen();

    private:
        std::vector<Components::CategoryUI> categories;
        bool toggled = false;
    };
}