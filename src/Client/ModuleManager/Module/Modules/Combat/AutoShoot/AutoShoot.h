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
				vManager.AddValue(autoPunch);
				vManager.AddValue(onlySniper);
				vManager.AddValue(onlyShotgun);
			};
			//autoPunch
			V::BooleanValue* autoPunch = new V::BooleanValue("AutoPunch", true);
			//onlySniper
			V::BooleanValue* onlySniper = new V::BooleanValue("OnlySniper", true);
			//onlyShotgun
			V::BooleanValue* onlyShotgun = new V::BooleanValue("OnlyShotgun", true);
			void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			bool getAutoPunch(C_TerrorWeapon *pWeapon);
		};
	}
};
