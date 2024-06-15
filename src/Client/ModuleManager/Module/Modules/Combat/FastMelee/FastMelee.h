#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
	namespace FastMeleeModule
	{
		class FastMelee : public Module
		{
		public:
			FastMelee()
			{
				this->Create("FastMelee", true, VK_NUMPAD1, ModuleCategory::Combat);
				vManager.AddValue(waitingTicks);
			};
			V::NumberValue *waitingTicks = new V::NumberValue("WaitingTicks", 4, 0, 20);

			bool shouldRun(C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal);
			void onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			bool isSwaping();
		private:
			bool nextSwap = false, buttonstate = false;
			// 0 = nothing, 1 = swap to primary or medkit grenade pills, 2 = swap to secondary
			int stage = 0, waiting = 0;
			void reset();
		};
	}
};
