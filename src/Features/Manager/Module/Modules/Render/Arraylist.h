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
				vManager.AddValue(arrayYPtr);
			};
			V::NumberValue arrayY = V::NumberValue("Arraylist Y", 100, 0, 1920);
			// arrayY pointer
			V::NumberValue* arrayYPtr = &arrayY;
			void onRender2D() override;
			V::ValueManager vManager;

		private:
		};
	};
};