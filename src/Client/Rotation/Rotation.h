#pragma once
#include "../../SDK/SDK.h"

namespace Helper
{
    class TurnSpeed
    {
    public:
        TurnSpeed(float yaw = 0.f, float pitch = 0.f) {
            this->yawTurnSpeed = yaw;
            this->pitchTurnSpeed = pitch;
        }
        float yawTurnSpeed;
        float pitchTurnSpeed;
    };
    
    class Rotation
    {
    public:
        Rotation(float yaw = 0.f, float pitch = 0.f)
        {
            this->yaw = yaw;
            this->pitch = pitch;
        };
        float yaw;
        float pitch;
        // toVector
        Vector toVector(){
            return Vector(pitch, yaw, 0.f);
        }

        Rotation toRotation(Vector aimVector) {
            return Rotation(aimVector.y, aimVector.x);
        }

        bool isZero() {
            return yaw == 0.f && pitch == 0.f;
        }
    };
}