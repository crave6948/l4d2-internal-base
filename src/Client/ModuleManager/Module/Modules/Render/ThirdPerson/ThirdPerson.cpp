#include "ThirdPerson.h"

namespace Client::Module
{
    namespace ThirdPersonModule {
        void ThirdPerson::onEnabled()
        {
            if (!I::IInput->m_fCameraInThirdPerson()) {
                I::IInput->m_fCameraInThirdPerson() = true;
                // I::IInput->CAM_ToThirdPerson();
            }
        }
        void ThirdPerson::onDisabled()
        {
            if (I::IInput->m_fCameraInThirdPerson()) {
                I::IInput->m_fCameraInThirdPerson() = false;
                // I::IInput->CAM_ToFirstPerson();
            }
        }
        void ThirdPerson::onRender2D()
        {
            std::string text = "Third Person : " + std::to_string(I::IInput->m_fCameraInThirdPerson());
            G::Draw.String(EFonts::DEBUG, G::Draw.m_nScreenW / 2, G::Draw.m_nScreenH / 2, Color(255, 255, 255, 255), TXT_CENTERXY, text.c_str());
            Vector pos = I::IInput->m_vecCameraOffset();
            std::string text2 = std::to_string(pos.x) + " " + std::to_string(pos.y) + " " + std::to_string(pos.z);
            G::Draw.String(EFonts::DEBUG, G::Draw.m_nScreenW / 2, G::Draw.m_nScreenH / 2 + 20, Color(255, 255, 255, 255), TXT_CENTERXY, text2.c_str());
        }
    }
}