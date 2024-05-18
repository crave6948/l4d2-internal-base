#pragma once
#include "MouseUtils.h"

namespace Client::Menu
{
    class Menu
    {
    public:
        void init();
        void toggle()
        {
            toggled = !toggled;
            if (toggled)
            {
                onEnabled();
            }
            else
            {
                onDisabled();
            }
        }
        void onEnabled();
        void onDisabled();

        void drawScreen();

        bool toggled = false;
    private:
        float popupanimate = 0.f;
    };
}