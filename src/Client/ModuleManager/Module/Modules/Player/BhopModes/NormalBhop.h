#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
    namespace BunnyHopModule
    {
        namespace BhopModes
        {
            class NormalBhop
            {
            public:
                void onPrePrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal);
                void onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags);
                void onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal);
                void onRender2D();
                void onChangeBhopType();
                void onDebug();
            private:
                int delayedTicks = 0;
                bool isJumping = false, nextGround = false;
                int oldbuttons = 0;
            };
            inline NormalBhop *NormalMode = new NormalBhop();
        }
    }
};