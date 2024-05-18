#include "MouseUtils.h"

namespace Client::Menu::MouseUtils
{
    void Mouse::update()
    {
        I::VGuiInput->GetCursorPos(mouse_x,mouse_y);
    }
}