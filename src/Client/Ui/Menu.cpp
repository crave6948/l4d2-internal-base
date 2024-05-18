#pragma once
#include "Menu.h"

namespace Client::Menu
{
    void Menu::init()
    {
    }

    void Menu::onEnabled()
    {
        popupanimate = 0.f;
        I::VGuiSurface->SetCursorAlwaysVisible(true);
    }

    void Menu::onDisabled()
    {
        I::VGuiSurface->SetCursorAlwaysVisible(false);
    }

    void Menu::drawScreen()
    {
        if (!this->toggled)
            return;
        // update mouse position
        MouseUtils::mouse.update();
        // get the mouse position
        auto [x, y] = MouseUtils::mouse.getMousePos();

        Color color = Color(255, 255, 255, 255);
        if (x > 100 && x < 100 + 100 && y > 100 && y < 100 + 100)
        {
            color = Color(255, 0, 0, 255);
        }
        G::Draw.OutlinedRect(100, 100, 100, 100, color);
        std::string mousePos = std::to_string(x) + ", " + std::to_string(y);
        G::Draw.String(EFonts::DEBUG, 100, 200, Color(255, 255, 255, 255), TXT_LEFT, mousePos.c_str());

        G::Draw.Rect(0, 0, (G::Draw.m_nScreenW * 0.3) * popupanimate, G::Draw.m_nScreenH, Color(255, 255, 255, 65));
        if (popupanimate < 1.0f)
        {
            popupanimate += 0.1f;
        }
    }
}