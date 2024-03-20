#include "NormalBhop.h"
#include "../BunnyHop.h"

namespace Client::Module::BunnyHopModule::BhopModes
{
    void NormalBhop::onPrePrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        oldbuttons = cmd->buttons;
        if (cmd->buttons & IN_JUMP)
            cmd->buttons &= ~IN_JUMP;
    }

    void NormalBhop::onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags)
    {
        nextGround = PredictedFlags & FL_ONGROUND;
    }

    void NormalBhop::onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
    {
        cmd->buttons = oldbuttons;
        if (cmd->buttons & IN_JUMP)
        {
            if (!(pLocal->m_fFlags() & FL_ONGROUND) && delayedTicks <= 0)
            {
                cmd->buttons &= ~IN_JUMP;
            }
            else if (pLocal->m_fFlags() & FL_ONGROUND || nextGround)
            {
                if (delayedTicks <= 0)
                    delayedTicks = Utils::RandomUtils::generateRandomNumber(10, 14);
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
        if (delayedTicks > 0)
            delayedTicks--;
    }

    void NormalBhop::onRender2D()
    {
    }
    void NormalBhop::onChangeBhopType()
    {
        delayedTicks = 0;
        isJumping = false;
        nextGround = false;
        oldbuttons = 0;
    }
    void NormalBhop::onDebug()
    {
        std::string str = "Bhop: " + std::to_string(delayedTicks) + " ticks / Jump:" + (isJumping ? "true" : "false") + " / Ground:" + (nextGround ? "true" : "false");
        G::Draw.String(EFonts::DEBUG, 100, 100, Color(255, 255, 255, 255), TXT_DEFAULT, str.c_str());
    }
};
