#pragma once
#include "Rotation.h"
#include "random"
namespace Helper
{
    class RotationManager
    {
    public:
        void moveTo(Rotation rotation, float targetDistance, bool isInCrosshair);
        void onUpdate();
        Rotation calculateRotation(Rotation currentRotation, Rotation targetRotation, float targetdistance, bool isInCrosshair);
        // get server rotation
        Rotation getServerRotation()
        {
            return serverRotation;
        };
        // get server rotation but return as Vector
        Vector getServerRotationVector()
        {
            return Vector(serverRotation.pitch, serverRotation.yaw, 0);
        };
        bool DisabledRotation = true;
        void ForceBack();

    private:
        Rotation serverRotation = Rotation();
        Rotation targetRotation;
        int keepTicks = 0;
        float targetDistance = 0.0f;
        bool isInCrosshair = false;
        int ticksToRotate = 0;
        int forceFocus = 0;
        float nextGassain(float min, float max)
        {
            std::default_random_engine generator;
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(generator);
        };
        Rotation clampRotation(Rotation rotation);
        Rotation getAngleDifference(Rotation a, Rotation b);
      
        // returns the turn speed for each axis
        TurnSpeed computeTurnSpeed(float distance, float diffH, float diffV, bool crosshair);
        float computeFactor(float rotationDifference, float turnSpeed);
    };
    inline RotationManager rotationManager = RotationManager();
}