#include "AutoShoot.h"
namespace F {
    namespace AutoShootModule {
        bool check = false;
        inline bool ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd)
		{
			if (cmd->buttons & IN_USE)
				return false;

			if (pLocal->m_isHangingFromLedge() || pLocal->m_isHangingFromTongue() || !pLocal->CanAttackFull())
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
            if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000) || !ShouldRun(pLocal, pWeapon, cmd)) {
                check = false;
                return;
            }
            if (cmd->buttons & IN_ATTACK) {
                bool WeaponAtk = pWeapon->CanPrimaryAttack();
                if (WeaponAtk) {
                    if (check) {
                        cmd->buttons &= ~IN_ATTACK;
                        check = false;
                    }
                    //next tick weapon shouldn't can attack
                    check = true;
                }else {
                    check = false;
                }
            }
        }
    }
}