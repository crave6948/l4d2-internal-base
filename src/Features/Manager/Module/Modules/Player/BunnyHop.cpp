#include "BunnyHop.h"
namespace F
{
	namespace BunnyHopModule
	{
		inline int delayedTicks = 0;
		inline bool isJumping = false, nextGround = false;
		void BunnyHop::onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags)
		{
			nextGround = PredictedFlags & FL_ONGROUND;
		}
		void BunnyHop::onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
		{
			if (cmd->buttons & IN_JUMP)
			{
				if (!nextGround && delayedTicks <= 0)
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
				if (delayedTicks > 0)
				{
					cmd->buttons |= IN_JUMP;
				}
			}
			isJumping = cmd->buttons & IN_JUMP;
			delayedTicks--;
		}

		void BunnyHop::onRender2D()
		{
			std::string str = "Bhop: " + std::to_string(delayedTicks) + " ticks / Jump:" + (isJumping ? "true" : "false") + " / Ground:" + (nextGround? "true" : "false");
			G::Draw.String(EFonts::DEBUG, 100, 100, Color(255, 255, 255, 255), TXT_DEFAULT, str.c_str());
		}
	}
}
