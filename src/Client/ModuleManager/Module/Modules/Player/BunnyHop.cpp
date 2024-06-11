#include "BunnyHop.h"
namespace Client::Module
{
	namespace BunnyHopModule
	{
		void BunnyHop::onPrePrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
		{
			if (this->isDisabledLookDown()) return;
			if (BhopType->GetSelected() == "Normal")
			{
				BhopModes::NormalMode->onPrePrediction(cmd, pWeapon, pLocal);
			}
		};
		void BunnyHop::onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags)
		{
			if (this->isDisabledLookDown()) return;
			if (BhopType->GetSelected() == "Normal")
			{
				BhopModes::NormalMode->onPrediction(cmd, pWeapon, pLocal, PredictedFlags);
			}
		};
		void BunnyHop::onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
		{
			if (this->isDisabledLookDown()) return;
			if (BhopType->GetSelected() == "Normal")
			{
				BhopModes::NormalMode->onPostPrediction(cmd, pWeapon, pLocal);
			}
		};
		void BunnyHop::onRender2D()
		{
			std::string currentMode = BhopType->GetSelected();
			// check if mode changed
			if (lastMode != currentMode)
			{
				lastMode = currentMode;
				needReset = true;
			}
			if (needReset)
			{
				if (currentMode == "Normal")
				{
					BhopModes::NormalMode->onChangeBhopType();
				}
				needReset = false;
			}
			if (BhopType->GetSelected() == "Normal")
			{
				BhopModes::NormalMode->onRender2D();
				if (Debug->GetValue())
				{
					BhopModes::NormalMode->onDebug();
				}
			}
		}
        bool BunnyHop::isDisabledLookDown()
        {
			Vector clientViewAngles;
			I::EngineClient->GetViewAngles(clientViewAngles);
            return this->DisableLookDown->GetValue() && clientViewAngles.x > 80.f;
        };
    }
};
