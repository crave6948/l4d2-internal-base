#include "FastMelee.h"
namespace Client::Module::FastMeleeModule
{
    inline bool nextSwap = false;
    // 0 = nothing, 1 = swap to primary or medkit grenade pills, 2 = swap to secondary
    inline int stage = 0, waiting = 0;
    bool FastMelee::shouldRun(C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        if (!pWeapon || !pLocal)
            return false;

        if (pWeapon->GetWeaponID() != WEAPON_MELEE)
            return false;

        if (!pWeapon->CanPrimaryAttack(-0.2))
            return false;

        return true;
    }
    void FastMelee::onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        if (nextSwap && stage > 0)
        {
            switch (stage)
            {
            case 1:
                if (waiting > 0)
                {
                    waiting--;
                    return;
                }
                for (int i = 0; i < 5; i++)
                {
                    if (i == 1)
                        continue;
                    C_BaseCombatWeapon *pWep = pLocal->Weapon_GetSlot(i);
                    if (!pWep)
                        continue;
                    if (pLocal->Weapon_CanSwitchTo(pWep))
                    {
                        cmd->weaponselect = pWep->entindex();
                        stage = 2;
                        waiting = 1;
                        break;
                    }
                }
                break;
            case 2:
                if (waiting > 0)
                {
                    waiting--;
                    return;
                }
                C_BaseCombatWeapon *pWep = pLocal->Weapon_GetSlot(1);
                if (!pWep)
                    return;
                if (pLocal->Weapon_CanSwitchTo(pWep))
                {
                    cmd->weaponselect = pWep->entindex();
                }
                stage = 0;
                nextSwap = false;
                break;
            }
            return;
        }
        if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
            stage = 0;
            nextSwap = false;
            waiting = 0;
            return;
        }
        if (!shouldRun(pWeapon, pLocal))
            return;
        nextSwap = true;
        stage = 1;
        waiting = 4;
    }
    void FastMelee::onRender2D()
    {
    }
    void FastMelee::onEnabled()
    {
    }
    void FastMelee::onDisabled()
    {
    }
}