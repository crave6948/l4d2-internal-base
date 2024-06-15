#include "NoSpread.h"
namespace Client::Module
{
	namespace NoSpreadModule
	{
		bool NoSpread::ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd)
		{
			if (!(cmd->buttons & IN_ATTACK) || (cmd->buttons & IN_USE))
				return false;

			if (!pLocal->CanAttackFull() || pLocal->m_isHangingFromLedge() || pLocal->m_isHangingFromTongue() || pLocal->m_isIncapacitated())
				return false;

			// You could also check if the current spread is -1.0f and not run nospread I guess.
			// But since I wanted to filter out shotungs and just be sure that it isnt ran for other stuff I check the weaponid.
			if (!pWeapon || !pWeapon->CanPrimaryAttack())
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
				return true;
			default:
				break;
			}

			return false;
		}

		void NoSpread::onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags)
		{
			static const auto pfSharedRandomFloat = reinterpret_cast<float (*)(const char *, float, float, int)>(U::Offsets.m_dwSharedRandomFloat);

			if (!ShouldRun(pLocal, pWeapon, cmd))
				return;

			Vector vAngle = cmd->viewangles;

			// Remove spread from current viewangles
			{
				const float flOldSpread = pWeapon->GetCurrentSpread();
				pWeapon->UpdateSpread();
				const float flSpread = pWeapon->GetCurrentSpread();

				vAngle.x -= pfSharedRandomFloat("CTerrorGun::FireBullet HorizSpread", -flSpread, flSpread, 0) * (spreadPercent->GetValue() / 100.0f);
				vAngle.y -= pfSharedRandomFloat("CTerrorGun::FireBullet VertSpread", -flSpread, flSpread, 0) * (spreadPercent->GetValue() / 100.0f);

				pWeapon->GetCurrentSpread() = flOldSpread;
			}

			// Remove punch from current viewangles
			if (removeRecoil->GetValue())
			{
				vAngle -= pLocal->GetPunchAngle();
			}

			U::Math.ClampAngles(vAngle);

			cmd->viewangles = vAngle;
		}
	}
}
