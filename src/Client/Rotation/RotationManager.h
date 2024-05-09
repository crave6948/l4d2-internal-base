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
        float nextGassain(float min, float max)
        {
            std::default_random_engine generator;
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(generator);
        };
        Rotation clampRotation(Rotation rotation);
        Rotation getAngleDifference(Rotation a, Rotation b);
        // returns the turn speed for each axis
        // TurnSpeed computeTurnSpeed(float distance, float diffH, float diffV, bool crosshair);
        // float coefDistance = -1.393f;
        // float coefDiffH = 0.21f;
        // float coefDiffV = 0.14f;
        // float coefCrosshairH = -5.99f;
        // float coefCrosshairV = -14.32f;
        // float interceptH = 11.988f;
        // float interceptV = 4.715f;
        // float minimumTurnSpeedH = 3.05e-5f;
        // float minimumTurnSpeedV = 5.96e-8f;
        float computeFactor(float rotationDifference, float turnSpeed);
        float min_horizontalTurnSpeed = 15;
        float max_horizontalTurnSpeed = 30;
        float min_verticalTurnSpeed = 10;
        float max_verticalTurnSpeed = 45;

        float steepness = 10.f;
        float midpoint = 0.3f;
    };
    inline RotationManager rotationManager = RotationManager();
}