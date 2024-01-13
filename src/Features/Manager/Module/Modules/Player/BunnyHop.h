#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace BunnyHopModule {
		class BunnyHop : public Module
		{
		public:
			BunnyHop() { this->Create("Bhop", true, VK_NUMPAD9); };
			void onPrediction(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal, int PredictedFlags) override;
			void onPostPrediction(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onRender2D() override;
		private:

		};
	};
};