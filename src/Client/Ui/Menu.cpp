#pragma once
#include "Menu.h"

namespace Client::Menu
{
    void Menu::init()
    {
        Components::CategoryUI categorie = Components::CategoryUI(200,200, 100,50, "HelloSir");
        categories.push_back(categorie);
    }

    void Menu::onEnabled()
    {
        I::VGuiSurface->SetCursorAlwaysVisible(true);
    }

    void Menu::onDisabled()
    {
        I::VGuiSurface->SetCursorAlwaysVisible(false);
    }

    void Menu::drawScreen()
    {
        if (!this->toggled) return;
        int x,y;
		// I::VGuiInput->GetCursorPos(x,y);
        I::VGuiSurface->SurfaceGetCursorPos(x,y);
        Color color = Color(255, 255, 255, 255);
        if (x > 100 && x < 100 + 100 && y > 100 && y < 100 + 100) {
            color = Color(255, 0, 0, 255);
        }
        G::Draw.OutlinedRect(100, 100, 100, 100, color);
        std::string mousePos = std::to_string(x) + ", " + std::to_string(y);
        G::Draw.String(EFonts::DEBUG,100,200,Color(255, 255, 255, 255),TXT_LEFT, mousePos.c_str());
        
        // loop through all the categories
        for (auto category : categories) {
            category.drawScreen(x,y);
        }
    }
}