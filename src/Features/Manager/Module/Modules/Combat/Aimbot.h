#pragma once
#include "../../ModuleHeader.h"
namespace F {
	namespace AimbotModule
	{
		class Aimbot : public Module
		{
		public:
			Aimbot() { this->Create("Aimbot", true, VK_NUMPAD7); };
			void onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onPostCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onRender2D() override;
			void onEnabled() override;
			void onDisabled() override;
		private:

		};
	}
};