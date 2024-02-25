#include "FastMelee.h"
namespace F::FastMeleeModule
{
    inline bool nextSwap = false;
    // 0 = nothing, 1 = swap to primary or medkit grenade pills, 2 = swap to secondary
    inline int stage = 0;
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
        if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
            stage = 0;
            nextSwap = false;
            return;
        }
        if (nextSwap && stage > 0)
        {
            switch (stage)
            {
            case 1:
                for (int i = 0; i < 5; i++)
                {
                    if (i == 1)
                        continue;
                    C_BaseCombatWeapon *pWep = pLocal->Weapon_GetSlot(i);
                    if (!pWep)
                        continue;
                    if (pLocal->Weapon_CanSwitchTo(pWep))
                    {
                        pLocal->SelectItem(pWep);
                        break;
                    }
                }
                stage = 2;
                break;
            case 2:
                C_BaseCombatWeapon *pWep = pLocal->Weapon_GetSlot(1);
                if (!pWep)
                    return;
                if (pLocal->Weapon_CanSwitchTo(pWep))
                {
                    pLocal->SelectItem(pWep);
                }
                stage = 0;
                nextSwap = false;
                break;
            }
            return;
        }
        if (!shouldRun(pWeapon, pLocal))
            return;
        nextSwap = true;
        stage = 1;
    }
    void FastMelee::onRender2D()
    {
        int startX = 100, startY = 100;
        std::string str = "Stage: " + std::to_string(stage) + " / NextSwap: " + (nextSwap ? "true" : "false");
        G::Draw.String(EFonts::DEBUG, startX, startY, Color(255, 255, 255, 255), TXT_DEFAULT, str.c_str());
    }
    void FastMelee::onEnabled()
    {
    }
    void FastMelee::onDisabled()
    {
    }
}