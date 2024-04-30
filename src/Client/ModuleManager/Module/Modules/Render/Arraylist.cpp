#include "Arraylist.h"
#include "../../../../None.h"

namespace Client::Module {
	namespace ArraylistModule {
		void Arraylist::onRender2D()
		{
			std::vector<Module*> list = Client::client.moduleManager.featurelist;
			int startX = G::Draw.m_nScreenW - 2, startY = 20;
			for (auto m : list) {
				std::string name = m->getName();
				bool isEnabled = m->getEnabled();
				if (isEnabled) {
					std::string str = name;
					int getFontWidth = G::Draw.GetFontWidth(EFonts::SDK_SC_WEB, str.c_str());
					int getFontHeight = G::Draw.GetFontHeight(EFonts::SDK_SC_WEB);
					G::Draw.Rect(startX - getFontWidth - 12 + m->animate, startY, getFontWidth, getFontHeight, Color(0, 0, 0, 170));
					G::Draw.Rect(startX - 10 + m->animate, startY, 10, getFontHeight, Color(255, 255, 255, 120));
					G::Draw.String(EFonts::SDK_SC_WEB, startX - 12 + m->animate, startY, Color(255, 255, 255, 255), TXT_LEFT, str.c_str());
					startY += getFontHeight + 1;
				}
				m->updateanimate();
			}
		}
	}
}
