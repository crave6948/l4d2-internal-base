#pragma once
#include "../../../SDK/SDK.h"

namespace Client::Menu
{
    namespace Components
    {
        class CategoryUI
        {
        public:
            CategoryUI(int x, int y, int w, int h, std::string name){
                this->x = x;
                this->y = y;
                this->width = w;
                this->height = h;
                this->name = name;
            };
            void drawScreen(int mouseX, int mouseY);

        private:
            int x, y, width, height;
            std::string name;
        };
    }
}