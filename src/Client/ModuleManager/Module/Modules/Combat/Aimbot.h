#pragma once
#include "../../ModuleHeader.h"
namespace Client::Module
{
	namespace AimbotModule
	{
		class Aimbot : public Module
		{
		public:
			Aimbot()
			{
				this->Create("Aimbot", true, VK_NUMPAD7);
				vManager.AddValue(fov);
				vManager.AddValue(silent);
				vManager.AddValue(switchDelay);
			};
			V::NumberValue *fov = new V::NumberValue("Fov", 180, 0, 180);
			V::BooleanValue *silent = new V::BooleanValue("Silent", true);
			V::NumberValue *switchDelay = new V::NumberValue("Switch Delay", 400, 0, 1000);
			void onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onRender2D() override;
			void onEnabled() override;
			void onDisabled() override;

		private:
		};
	}
};