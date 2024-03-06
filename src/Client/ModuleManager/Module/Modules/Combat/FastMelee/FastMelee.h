#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module {
	namespace FastMeleeModule
	{
		class FastMelee : public Module
		{
		public:
			FastMelee() { this->Create("FastMelee", true, VK_NUMPAD1); };
			bool shouldRun(C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal);
			void onPostCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onRender2D() override;
			void onEnabled() override;
			void onDisabled() override;
		};
	}
};