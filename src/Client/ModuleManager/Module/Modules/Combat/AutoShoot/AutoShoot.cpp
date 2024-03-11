#include "AutoShoot.h"
namespace Client::Module
{
	namespace AutoShootModule
	{
		int check = false;
		bool nextPunch = false;
		inline bool isSniper(int id)
		{
			return (id == WEAPON_AWP || id == WEAPON_SCOUT);
		}
		inline bool isShotgun(int id)
		{
			return (id == WEAPON_PUMP_SHOTGUN || id == WEAPON_CHROME_SHOTGUN);
		}
		inline bool ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd)
		{
			if (cmd->buttons & IN_USE)
				return false;

			if (pLocal->m_isHangingFromLedge() || pLocal->m_isHangingFromTongue() || pWeapon->m_bInReload())
				return false;

			// You could also check if the current spread is -1.0f and not run nospread I guess.
			// But since I wanted to filter out shotungs and just be sure that it isnt ran for other stuff I check the weaponid.
			if (!pWeapon)
				return false;
			switch (pWeapon->GetWeaponID())
			{
			case WEAPON_AK47:
			case WEAPON_AWP:
			case WEAPON_DEAGLE:
			case WEAPON_HUNTING_RIFLE:
			case WEAPON_M16A1:
			case WEAPON_M60:
			case WEAPON_MAC10:
			case WEAPON_MILITARY_SNIPER:
			case WEAPON_MP5:
			case WEAPON_PISTOL:
			case WEAPON_SCAR:
			case WEAPON_SCOUT:
			case WEAPON_SSG552:
			case WEAPON_UZI:
			case WEAPON_AUTO_SHOTGUN:
			case WEAPON_SPAS:
			case WEAPON_PUMP_SHOTGUN:
			case WEAPON_CHROME_SHOTGUN:
				return true;
			default:
				break;
			}

			return false;
		}
		void AutoShoot::onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
		{
			if (!ShouldRun(pLocal, pWeapon, cmd))
			{
				check = false;
				nextPunch = false;
				return;
			}

			if (nextPunch)
			{
				if (cmd->buttons & IN_ATTACK2)
				{
					cmd->buttons &= ~IN_ATTACK2;
				}else {
					bool attack = pLocal->IsReadyToShove() || pWeapon->CanSecondaryAttack(-0.1);
					if (attack)
					{
						cmd->buttons |= IN_ATTACK2;
					}
					nextPunch = false;
				}
			}

			if (cmd->buttons & IN_ATTACK)
			{
				bool attack = pWeapon->CanPrimaryAttack(-0.1);
				if (attack)
				{
					if (check)
					{
						cmd->buttons &= ~IN_ATTACK;
						check = false;
					}
					else
					{
						check = true;
					}
					if (getAutoPunch(pWeapon))
						nextPunch = true;
				}
				else
				{
					check = false;
				}
			}else {
				check = false;
			}
		}
		bool AutoShoot::getAutoPunch(C_TerrorWeapon *pWeapon)
		{
			if (!autoPunch->GetValue())
				return false;
			if (!onlySniper->GetValue() && !onlyShotgun->GetValue())
				return true;
			int id = pWeapon->GetWeaponID();
			if (onlySniper->GetValue() && isSniper(id))
				return true;
			if (onlyShotgun->GetValue() && isShotgun(id))
				return true;
			return false;
		}
	}
}