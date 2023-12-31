#include "BunnyHop.h"
#include <random>
namespace F {
	namespace BunnyHopModule {
		int generateRandomNumber(int min, int max) {
			std::random_device rd;

			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> distribution(min, max);

			int random_number = distribution(gen);

			return random_number;
		}
		inline int delayedTicks = 13;
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
						delayedTicks = generateRandomNumber(13,20);
					}
				}
			}
		}

		void BunnyHop::onRender2D()
		{
		}
	}
}
