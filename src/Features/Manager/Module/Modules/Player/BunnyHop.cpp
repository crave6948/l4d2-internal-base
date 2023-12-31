#include "BunnyHop.h"
#include <random>
namespace F {
	namespace BunnyHopModule {
		inline int delayedTicks = 0;
		void BunnyHop::onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal)
		{
			if (cmd->buttons & IN_JUMP) {
				if (!(pLocal->m_fFlags() & FL_ONGROUND)) {
					cmd->buttons &= ~IN_JUMP;
				}else {
					if (delayedTicks > 0) {
						cmd->buttons &= ~IN_JUMP;
						delayedTicks--;
					}else {
						delayedTicks = 1;
					}
				}
			}else {
				delayedTicks = 0;
			}
		}

		void BunnyHop::onRender2D()
		{
		}
	}
}
