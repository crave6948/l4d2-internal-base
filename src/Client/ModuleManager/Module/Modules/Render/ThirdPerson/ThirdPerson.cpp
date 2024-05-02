#include "ThirdPerson.h"

namespace Client::Module
{
    namespace ThirdPersonModule
    {
        void ThirdPerson::onRender2D()
        {
            if (!debug->GetValue())
                return;
            std::string text = "Third Person : " + std::to_string(I::IInput->m_fCameraInThirdPerson());
            G::Draw.String(EFonts::DEBUG, G::Draw.m_nScreenW / 2, G::Draw.m_nScreenH / 2, Color(255, 255, 255, 255), TXT_CENTERXY, text.c_str());
            Vector pos = I::IInput->m_vecCameraOffset();
            std::string text2 = std::to_string(pos.x) + " " + std::to_string(pos.y) + " " + std::to_string(pos.z);
            G::Draw.String(EFonts::DEBUG, G::Draw.m_nScreenW / 2, G::Draw.m_nScreenH / 2 + 20, Color(255, 255, 255, 255), TXT_CENTERXY, text2.c_str());
        }
        void ThirdPerson::onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
        {
            rotation = cmd->viewangles;
        }
        void ThirdPerson::onFrameStageNotify(ClientFrameStage_t curStage)
        {
            if (!I::EngineClient->IsConnected() || !I::EngineClient->IsInGame() || I::EngineVGui->IsGameUIVisible())
                return;
            static bool is_clicking = false;
            // toggle
            {
                if (GetAsyncKeyState(0x56) & 0x8000)
                {
                    if (!is_clicking)
                        isThirdPerson = !isThirdPerson;
                    is_clicking = true;
                }
                else
                    is_clicking = false;
            }
            C_TerrorPlayer *pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer *>();
            if (pLocal != nullptr)
            {
                if (isThirdPerson)
                {
	                I::Prediction->SetLocalViewAngles(rotation);
                    I::IInput->m_fCameraInThirdPerson() = true;
                    I::Cvar->FindVar("cam_idealdist")->SetValue(distance->GetValue());
                    I::Cvar->FindVar("cam_collision")->SetValue(true);
                    I::Cvar->FindVar("cam_snapto")->SetValue(true);
                    I::Cvar->FindVar("c_thirdpersonshoulder")->SetValue(true);
                    I::Cvar->FindVar("c_thirdpersonshoulderaimdist")->SetValue(0.f);
                    I::Cvar->FindVar("c_thirdpersonshoulderdist")->SetValue(0.f);
                    I::Cvar->FindVar("c_thirdpersonshoulderheight")->SetValue(0.f);
                    I::Cvar->FindVar("c_thirdpersonshoulderoffset")->SetValue(0);
                }
                else
                {
                    I::IInput->m_fCameraInThirdPerson() = false;
                }
            }
        }
    }
}