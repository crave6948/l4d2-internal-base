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
				this->Create("ESPHelper", true, VK_RIGHT, Client::Module::ModuleCategory::Visuals);
			};
			void onRender2D() override;

		private:
		};
	};
};