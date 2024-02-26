#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace NoSpreadModule {
		class NoSpread : public Module
		{
		public:
			NoSpread() { this->Create("NoSpread", true, VK_NUMPAD8); };
			void onPrediction(CUserCmd* cmd,C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal, int PredictedFlags) override;
		private:

		};
	};
};