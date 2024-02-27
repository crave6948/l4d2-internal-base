#include "Arraylist.h"
#include "../../../Manager.h"

namespace F {
	namespace ArraylistModule {
		void Arraylist::onRender2D()
		{
			std::vector<Module*> list = F::FeatureManager.featurelist;
			int startX = G::Draw.m_nScreenW - 2, startY = 20;
			for (auto m : list) {
				std::string name = m->getName();
				bool isEnabled = m->getEnabled();
				if (isEnabled) {
					std::string str = name;
					G::Draw.Rect(startX - G::Draw.GetFontWidth(EFonts::DEBUG, str.c_str()) - 12 + m->animate, startY, G::Draw.GetFontWidth(EFonts::DEBUG, str.c_str()), G::Draw.GetFontHeight(EFonts::DEBUG), Color(0, 0, 0, 170));
					G::Draw.Rect(startX - 10 + m->animate, startY, 10, G::Draw.GetFontHeight(EFonts::DEBUG), Color(255, 255, 255, 120));
					G::Draw.String(EFonts::DEBUG, startX - 12 + m->animate, startY, Color(255, 255, 255, 255), TXT_LEFT, str.c_str());
					startY += G::Draw.GetFontHeight(EFonts::DEBUG) + 1;
				}
				m->updateanimate();
			}
		}
	}
}
