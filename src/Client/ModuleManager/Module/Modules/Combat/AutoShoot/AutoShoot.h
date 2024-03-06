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
				this->Create("AutoShoot", true, VK_NUMPAD2);
				vManager.AddValue(&autoPunch);
				vManager.AddValue(&onlySniper);
				vManager.AddValue(&onlyShotgun);
			};
			//autoPunch
			V::BooleanValue autoPunch = V::BooleanValue("AutoPunch", true);
			V::BooleanValue* autoPunchptr = &autoPunch;
			//onlySniper
			V::BooleanValue onlySniper = V::BooleanValue("OnlySniper", true);
			V::BooleanValue* onlySniperptr = &onlySniper;
			//onlyShotgun
			V::BooleanValue onlyShotgun = V::BooleanValue("OnlyShotgun", true);
			V::BooleanValue* onlyShotgunptr = &onlyShotgun;
			void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			bool getAutoPunch(C_TerrorWeapon *pWeapon);
		};
	}
};
