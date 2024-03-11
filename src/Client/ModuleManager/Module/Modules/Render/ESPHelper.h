#pragma once
#include "../../ModuleHeader.h"

namespace Client::Module
{
	namespace ESPHelperModule
	{
		class ESPHelper : public Module
		{
		public:
			ESPHelper()
			{
				this->Create("ESPHelper", true, VK_RIGHT, ModuleCategory::Visuals);
			};
			void onRender2D() override;

		private:
			void drawESP(C_BaseEntity *pBaseEntity, int hit);
		};
	};
};