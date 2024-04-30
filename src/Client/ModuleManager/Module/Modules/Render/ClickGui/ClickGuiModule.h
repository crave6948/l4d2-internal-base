#pragma once
// Start from ClickGui ../Render ../Modules ../Module /ModuleHeader.h 
#include "../../../ModuleHeader.h"

namespace Client::Module
{
	namespace ClickGuiModule
	{
		class ClickGui : public Module
		{
		public:
			ClickGui()
			{
				this->Create("ClickGui", true, VK_RSHIFT, ModuleCategory::Visuals);
				vManager = V::ValueManager();
			};
            void onEnabled() override;
			V::ValueManager vManager;

		private:
		};
	};
};