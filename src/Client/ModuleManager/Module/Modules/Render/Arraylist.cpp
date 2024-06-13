#include "Arraylist.h"
#include "../../../../None.h"
#include <chrono>

namespace Client::Module
{
	namespace ArraylistModule
	{
		void Arraylist::onRender2D()
		{
			std::vector<Module *> list = Client::client.moduleManager.featurelist;
			// sort vector by font width with it name
			std::sort(list.begin(), list.end(), [](Module *a, Module *b)
					  {
        int fontWidthA = G::Draw.GetFontWidth(EFonts::Greycliff_CF, a->getName().c_str());
        int fontWidthB = G::Draw.GetFontWidth(EFonts::Greycliff_CF, b->getName().c_str());
        return fontWidthA > fontWidthB; });

			int startX = G::Draw.m_nScreenW - 2, startY = 0;

			// Get a "time-based" hue value
			auto now = std::chrono::high_resolution_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
			float hue = static_cast<float>((time % 3600) / 10.0f); // Cycle through 360 degrees every 3600 milliseconds

			for (auto m : list)
			{
				std::string name = m->getName();
				bool isEnabled = m->getEnabled();
				if (isEnabled)
				{
					std::string str = name;
					int getFontWidth = G::Draw.GetFontWidth(EFonts::Greycliff_CF, str.c_str());
					int getFontHeight = G::Draw.GetFontHeight(EFonts::Greycliff_CF);

					// Use the HSV to RGB conversion for a rainbow effect
					Color rainbowColor = HSVtoRGB(hue, 100, 100);

					G::Draw.Rect(startX - 4 - getFontWidth + m->animate, startY, getFontWidth, getFontHeight, Color(0, 0, 0, 170));
					G::Draw.Rect(startX - 4 + m->animate, startY, 10, getFontHeight, rainbowColor);
					G::Draw.String(EFonts::Greycliff_CF, startX - 4 + m->animate, startY, rainbowColor, TXT_LEFT, str.c_str());
					startY += getFontHeight;
				}
				m->updateanimate();
				hue += 10; // Change the hue for each item to get a "gradient" effect
				if (hue > 360)
					hue -= 360; // Keep the hue value within 0-360
			}
		}
	}
}
