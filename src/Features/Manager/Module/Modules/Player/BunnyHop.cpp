#include "BunnyHop.h"
namespace F
{
	namespace BunnyHopModule
	{
		inline int delayedTicks = 0;
		void BunnyHop::onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
		{
			if (cmd->buttons & IN_JUMP)
			{
				if (!(pLocal->m_fFlags() & FL_ONGROUND) && delayedTicks <= 0)
				{
					cmd->buttons &= ~IN_JUMP;
				}
				else if (pLocal->m_fFlags() & FL_ONGROUND)
				{
					delayedTicks = Utils::RandomUtils::generateRandomNumber(5, 9);
				}
			}
			else
			{
				if (delayedTicks > 0) {
					cmd->buttons |= IN_JUMP;
				}
			}

			if (delayedTicks > 0)
			{
				delayedTicks--;
			}
		}

		void BunnyHop::onRender2D()
		{
		}
	}
}
