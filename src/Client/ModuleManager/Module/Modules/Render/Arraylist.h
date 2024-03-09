#pragma once
#include "../../ModuleHeader.h"

namespace Client::Module
{
	namespace ArraylistModule
	{
		class Arraylist : public Module
		{
		public:
			Arraylist()
			{
				this->Create("ArrayList", true, VK_NUMPAD0, Client::Module::ModuleCategory::Visuals);
				vManager = V::ValueManager();
			};
			void onRender2D() override;
			V::ValueManager vManager;

		private:
		};
	};
};