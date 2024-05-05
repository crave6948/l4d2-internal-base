#pragma once

#include "../Includes/ehandle.h"

class bf_write;
class bf_read;
class kbutton_t;
class CUserCmd;
class C_BaseCombatWeapon;
class ButtonCode_t;

struct CameraThirdData_t
{
    float   m_flPitch;
    float   m_flYaw;
    float   m_flDist;
    float   m_flLag;
    Vector  m_vecHullMin;
    Vector  m_vecHullMax;
};

// class CVerifiedUserCmd
// {
// public:
//     CUserCmd m_cmd;
//     CRC32_t m_crc;
// };

struct IInput_t
{
     // Initialization/shutdown of the subsystem
    virtual void        Init_All(void) = 0;
    virtual void        Shutdown_All(void) = 0;
    // Latching button states
    virtual int         GetButtonBits(int) = 0;
    // Create movement command
    virtual void        CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
    virtual void        ExtraMouseSample(float frametime, bool active) = 0;
    virtual bool        WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand) = 0;
    virtual void        EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
    virtual void        DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;

    virtual CUserCmd*   GetUserCmd(int sequence_number) = 0;

    virtual void        MakeWeaponSelection(C_BaseCombatWeapon* weapon) = 0;

    // Retrieve key state
    virtual float       KeyState(kbutton_t* key) = 0;
    // Issue key event
    virtual int         KeyEvent(int eventcode, ButtonCode_t keynum, const char* pszCurrentBinding) = 0;
    // Look for key
    virtual kbutton_t* FindKey(const char* name) = 0;

    // Issue commands from controllers
    virtual void        ControllerCommands(void) = 0;
    // Extra initialization for some joysticks
    virtual void        Joystick_Advanced(void) = 0;
    virtual void        Joystick_SetSampleTime(float frametime) = 0;
    virtual void        IN_SetSampleTime(float frametime) = 0;

    // Accumulate mouse delta
    virtual void        AccumulateMouse(void) = 0;
    // Activate/deactivate mouse
    virtual void        ActivateMouse(void) = 0;
    virtual void        DeactivateMouse(void) = 0;

    // Clear mouse state data
    virtual void        ClearStates(void) = 0;
    // Retrieve lookspring setting
    virtual float       GetLookSpring(void) = 0;

    // Retrieve mouse position
    virtual void        GetFullscreenMousePos(int* mx, int* my, int* unclampedx = 0, int* unclampedy = 0) = 0;
    virtual void        SetFullscreenMousePos(int mx, int my) = 0;
    virtual void        ResetMouse(void) = 0;
    virtual float       GetLastForwardMove(void) = 0;
    virtual float       Joystick_GetForward(void) = 0;
    virtual float       Joystick_GetSide(void) = 0;
    virtual float       Joystick_GetPitch(void) = 0;
    virtual float       Joystick_GetYaw(void) = 0;

    // Third Person camera ( TODO/FIXME:  Move this to a separate interface? )
    virtual void        CAM_Think(void) = 0;
    virtual int         CAM_IsThirdPerson(void) = 0;
    virtual void        CAM_ToThirdPerson(void) = 0;
    virtual void        CAM_ToFirstPerson(void) = 0;
    virtual void        CAM_StartMouseMove(void) = 0;
    virtual void        CAM_EndMouseMove(void) = 0;
    virtual void        CAM_StartDistance(void) = 0;
    virtual void        CAM_EndDistance(void) = 0;
    virtual int         CAM_InterceptingMouse(void) = 0;

    // orthographic camera info ( TODO/FIXME:  Move this to a separate interface? )
    virtual void        CAM_ToOrthographic() = 0;
    virtual bool        CAM_IsOrthographic() const = 0;
    virtual void        CAM_OrthographicSize(float& w, float& h) const = 0;

    virtual void        LevelInit(void) = 0;

    // Causes an input to have to be re-pressed to become active
    virtual void        ClearInputButton(int bits) = 0;

    virtual void        CAM_SetCameraThirdData(CameraThirdData_t* pCameraData, const Vector& vecCameraOffset) = 0;
    virtual void        CAM_CameraThirdThink(void) = 0;

    virtual bool        EnableJoystickMode() = 0;
    //48
// private:
//     char __pad01[0xB1];

public:
    // bool m_fCameraInThirdPerson; // 0x00B1
    bool& m_fCameraInThirdPerson() {
		return *reinterpret_cast<bool*>(reinterpret_cast<DWORD>(this) + 0x00B1);
	}
// private:
//     char __pad02[0x2];

public:
    // Vector ThirdpersonCameraAngle; // 0x00B4
    // Vector m_vecCameraOffset; // 0x00B4
    Vector& m_vecCameraOffset() {
        // return reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(this) + 0x00B4);
        return *reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(this) + 0x00B4);
    }
// private:
//     char __pad03[0x2C];

// public:
//     CUserCmd *m_pCommands;                 // 0x00EC
    // CVerifiedUserCmd *m_pVerifiedCommands; // 0x00F0
};

namespace I { inline IInput_t* IInput = nullptr; }