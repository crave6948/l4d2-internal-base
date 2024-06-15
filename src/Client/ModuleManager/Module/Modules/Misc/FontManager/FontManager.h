#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
	namespace FontManagerModule
	{
		class FontManager : public Module
		{
		public:
			FontManager()
			{
				this->Create("FontManager", false, 0, ModuleCategory::Misc);
                vManager.AddValue(fontSize);
			};
            V::NumberValue* fontSize = new V::NumberValue("Font Size", 24, 12, 72);
		};
	};
};