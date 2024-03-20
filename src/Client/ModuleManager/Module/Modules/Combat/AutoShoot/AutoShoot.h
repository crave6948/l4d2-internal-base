#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
	namespace AutoShootModule
	{
		class AutoShoot : public Module
		{
		public:
			AutoShoot()
			{
				this->Create("AutoShoot", true, VK_NUMPAD2, ModuleCategory::Combat);
				vManager.AddValue(autoPunch);
				vManager.AddValue(onlySniper);
				vManager.AddValue(onlyShotgun);
				vManager.AddValue(keepForTicks);
				vManager.AddValue(Debug);
			};
			// autoPunch
			V::BooleanValue *autoPunch = new V::BooleanValue("AutoPunch", true);
			// onlySniper
			V::BooleanValue *onlySniper = new V::BooleanValue("OnlySniper", true);
			// onlyShotgun
			V::BooleanValue *onlyShotgun = new V::BooleanValue("OnlyShotgun", true);
			// waitForTicks
			V::NumberValue *keepForTicks = new V::NumberValue("KeepForTicks", 10, 0, 20, "ticks");
			// Debug
			V::BooleanValue *Debug = new V::BooleanValue("Debug", false);
			
			void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onRender2D() override;
			bool getAutoPunch(C_TerrorWeapon *pWeapon);

		private:
			int keepClicks = 0;
			bool nextPunch = false;
			bool isSniper(int id);
			bool isShotgun(int id);
			bool ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd);
			bool isClicking = false;
		};
	}
};
