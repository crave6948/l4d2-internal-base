#include "BunnyHop.h"
#include <random>
namespace F
{
	namespace BunnyHopModule
	{
		inline int delayedTicks = 0;
		inline int generateRandomNumber(int min, int max)
		{
			// Use a random_device to seed the random number generator
			std::random_device rd;

			// Use the random_device to seed the Mersenne Twister PRNG
			std::mt19937 gen(rd());

			// Define a range for the random numbers
			std::uniform_int_distribution<int> distribution(min, max);

			// Generate a random number within the specified range
			int random_number = distribution(gen);

			return random_number;
		}
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
					delayedTicks = generateRandomNumber(4, 6);
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
