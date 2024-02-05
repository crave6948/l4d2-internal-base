#pragma once
#include "../../../ModuleHeader.h"

namespace F {
	namespace AutoShootModule
	{
		class AutoShoot : public Module
		{
		public:
			AutoShoot() { this->Create("AutoShoot", true, VK_NUMPAD2); };
			void onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onPostCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onRender2D() override;
			void onEnabled() override;
			void onDisabled() override;
		private:

		};
	}
};
