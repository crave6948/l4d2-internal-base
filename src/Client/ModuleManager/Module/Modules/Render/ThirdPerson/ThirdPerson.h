#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
	namespace ThirdPersonModule
	{
		class ThirdPerson : public Module
		{
		public:
			ThirdPerson()
			{
				this->Create("ThirdPerson", false, 0x56, ModuleCategory::Visuals);
				vManager = V::ValueManager();
			};
            void onEnabled() override;
			void onDisabled() override;
			void onRender2D() override;
			V::ValueManager vManager;
		};
	};
};