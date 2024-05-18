#pragma once
#include "../../SDK/SDK.h"

namespace Client::Menu
{
    namespace MouseUtils
    {
        class Mouse
        {
            public:
            void update();
            std::pair<int,int> getMousePos(){ return std::make_pair(mouse_x, mouse_y); };
            private:
            int mouse_x, mouse_y;
        };
        inline Mouse mouse;
    }
}