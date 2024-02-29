#pragma once
#include "../../ModuleHeader.h"

namespace F
{
	namespace ArraylistModule
	{
		class Arraylist : public Module
		{
		public:
			Arraylist()
			{
				this->Create("ArrayList", true, VK_NUMPAD0);
				vManager = V::ValueManager();
			};
			void onRender2D() override;
			V::ValueManager vManager;

		private:
		};
	};
};