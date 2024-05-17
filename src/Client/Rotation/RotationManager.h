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
        TurnSpeed computeTurnSpeed(float distance, float diffH, float diffV, bool crosshair);
        // float coefDistance = -0.14f; // aim accuracy
        // float coefDiffH = 0.3f; // horizontal starting aim speed
        // float coefDiffV = 0.3f; // vertical starting aim speed
        // float coefCrosshairH = -13.8f; // horizontal aim jitter while tracking enemy
        // float coefCrosshairV = -14.4f; // vertical aim jitter while tracking enemy
        // float interceptH = 12.f; // horizontal rotation speed while attacking
        // float interceptV = 4.7f; // vertical rotation speed while attacking
        // float minimumTurnSpeedH = 0; // minimum horizontal rotation speed
        // float minimumTurnSpeedV = 0; // minimum vertical rotation speed
        float computeFactor(float rotationDifference, float turnSpeed);
        // float min_horizontalTurnSpeed = 0.2;
        // float max_horizontalTurnSpeed = 25;
        // float min_verticalTurnSpeed = 0.2;
        // float max_verticalTurnSpeed = 45;

        // float steepness = 10.5f;
        // float midpoint = 0.3f;
    };
    inline RotationManager rotationManager = RotationManager();
}