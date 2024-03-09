#pragma once
#include "../../ModuleHeader.h"

namespace Client::Module
{
	namespace NoSpreadModule
	{
		class NoSpread : public Module
		{
		public:
			NoSpread()
			{
				this->Create("NoSpread", true, VK_NUMPAD8, Client::Module::ModuleCategory::Combat);
				vManager.AddValue(removeRecoil);
				vManager.AddValue(spreadPercent);
			};
			V::BooleanValue *removeRecoil = new V::BooleanValue("RemoveRecoil", true);
			V::NumberValue *spreadPercent = new V::NumberValue("SpreadPercent", 100, 0, 100, "Percent");
			void onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags) override;

		private:
		};
	};
};