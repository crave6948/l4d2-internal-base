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
				this->Create("ArrayList", true, VK_NUMPAD0, ModuleCategory::Visuals);
			};
			void onRender2D() override;

		private:
			Color HSVtoRGB(float H, float S, float V, int A = 255)
			{
				float s = S / 100.0f;
				float v = V / 100.0f;
				float C = s * v;
				float X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
				float m = v - C;
				float r, g, b;
				if (H >= 0 && H < 60)
				{
					r = C, g = X, b = 0;
				}
				else if (H >= 60 && H < 120)
				{
					r = X, g = C, b = 0;
				}
				else if (H >= 120 && H < 180)
				{
					r = 0, g = C, b = X;
				}
				else if (H >= 180 && H < 240)
				{
					r = 0, g = X, b = C;
				}
				else if (H >= 240 && H < 300)
				{
					r = X, g = 0, b = C;
				}
				else
				{
					r = C, g = 0, b = X;
				}
				int R = (r + m) * 255;
				int G = (g + m) * 255;
				int B = (b + m) * 255;
				return Color(R, G, B, A);
			};
		};
	};
};