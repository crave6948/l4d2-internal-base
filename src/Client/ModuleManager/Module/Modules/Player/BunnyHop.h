#pragma once
#include "BhopModes/NormalBhop.h"
namespace Client::Module
{
	namespace BunnyHopModule
	{
		class BunnyHop : public Module
		{
		public:
			BunnyHop()
			{
				this->Create("Bhop", true, VK_NUMPAD9, ModuleCategory::Player);
				vManager.AddValue(BhopType);
				vManager.AddValue(Debug);
			};
			V::ListValue *BhopType = new V::ListValue("BhopType", std::vector<std::string>{"Normal", "Legit", "Rage"}, std::string("Normal"));
			V::BooleanValue *Debug = new V::BooleanValue("Debug", false);

			void onPrePrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags) override;
			void onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onRender2D() override;

		private:
			bool needReset = false;
			std::string lastMode = "Normal";
		};
	};
};