#include "FastMelee.h"
namespace Client::Module::FastMeleeModule
{
    bool FastMelee::shouldRun(C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        if (!pWeapon || !pLocal || pLocal->m_isIncapacitated() || !pLocal->CanAttackFull())
            return false;

        if (pWeapon->GetWeaponID() != WEAPON_MELEE)
            return false;

        if (!pWeapon->CanPrimaryAttack(-0.2))
            return false;

        return true;
    }
    void FastMelee::onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        buttonstate = (cmd->buttons & IN_ATTACK) != 0;
    }
    void FastMelee::onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        if (!pLocal || pLocal->m_isIncapacitated())
        {
            reset();
            return;
        }
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
        // if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
        if (!(buttonstate))
        {
            reset();
            return;
        }
        if (!shouldRun(pWeapon, pLocal))
            return;
        nextSwap = true;
        stage = 1;
        waiting = waitingTicks->GetValue();
    }
    bool FastMelee::isSwaping()
    {
        return nextSwap && stage > 0;
    }
    void FastMelee::reset()
    {
        stage = 0;
        nextSwap = false;
        waiting = 0;
    }
}