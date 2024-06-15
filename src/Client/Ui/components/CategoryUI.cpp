#pragma once
#include "CategoryUI.h"

namespace Client::Menu
{
    namespace Components
    {
        void CategoryUI::drawScreen(int mouseX, int mouseY)
        {
            int centerX = (x + x + width) / 2;
            int centerY = (y + y + height) / 2;
            G::Draw.Rect(this->x, this->y, this->width, this->height, Color(255, 255, 255, 125));
            G::Draw.OutlinedRect(this->x, this->y, this->width, this->height, Color(255, 255, 255, 255));
            G::Draw.String(EFonts::DEBUG, centerX, centerY, Color(255, 255, 255, 255), TXT_CENTERXY, this->name.c_str());
        }
    }
}