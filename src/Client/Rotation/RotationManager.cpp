#include "RotationManager.h"

namespace Helper
{
    void RotationManager::moveTo(Rotation rotation, float targetDistance, bool isInCrosshair)
    {
        this->targetRotation = rotation;
        this->targetDistance = targetDistance;
        this->isInCrosshair = isInCrosshair;
        this->keepTicks = TIME_TO_TICKS(1);
        this->DisabledRotation = false;
    }
    void RotationManager::onUpdate()
    {
        if (DisabledRotation || serverRotation.isZero())
        {
            Vector viewAngles;
            I::EngineClient->GetViewAngles(viewAngles);
            Rotation rotation = Rotation(viewAngles.y, viewAngles.x);
            serverRotation = rotation;
            ticksToRotate = 0;
        }
        bool isReseting = false;
        if (this->keepTicks <= 0)
        {
            isReseting = true;
        }
        else
        {
            this->keepTicks--;
        }
        if (ticksToRotate > 0)
        {
            ticksToRotate--;
        }
        else
        {
            if (isReseting)
            {
                if (DisabledRotation)
                    return;
                Vector viewAngles;
                I::EngineClient->GetViewAngles(viewAngles);
                Rotation rotation = Rotation(viewAngles.y, viewAngles.x);
                serverRotation = calculateRotation(serverRotation, rotation, 0.f, false);
                float rotationDifference = U::Math.GetFovBetween(serverRotation.toVector(), rotation.toVector());
                if (rotationDifference <= 1.f)
                    DisabledRotation = true;
            }
            else
            {
                serverRotation = calculateRotation(serverRotation, targetRotation, targetDistance, isInCrosshair);
            }
            ticksToRotate = TIME_TO_TICKS(0.01);
        }
    }
    Rotation RotationManager::calculateRotation(Rotation currentRotation, Rotation targetRotation, float targetdistance = 0.f, bool isInCrosshair = false)
    {
        Rotation angleDifference = getAngleDifference(currentRotation, targetRotation);
        float rotationDifference = U::Math.GetFovBetween(currentRotation.toVector(), targetRotation.toVector());
        Rotation rotation;
        // get turnspeed from computeTurnSpeed function
        // TurnSpeed turnSpeed = this->computeTurnSpeed(
        //     targetdistance,
        //     abs(angleDifference.yaw),
        //     abs(angleDifference.pitch),
        //     isInCrosshair);

        // random horizontal and vertical turnspeeds
        float randomYaw = nextGassain(min_horizontalTurnSpeed, max_horizontalTurnSpeed);
        float randomPitch = nextGassain(min_verticalTurnSpeed, max_verticalTurnSpeed);
      
        TurnSpeed turnSpeed = TurnSpeed(computeFactor(rotationDifference, randomYaw), computeFactor(rotationDifference, randomPitch));
        // float straightLineYaw = std::max(abs(angleDifference.yaw / rotationDifference) * turnSpeed.yawTurnSpeed, minimumTurnSpeedH);
        // float straightLinePitch = std::max(abs(angleDifference.pitch / rotationDifference) * turnSpeed.pitchTurnSpeed, minimumTurnSpeedV);
        float straightLineYaw = abs(angleDifference.yaw / rotationDifference) * turnSpeed.yawTurnSpeed;
        float straightLinePitch = abs(angleDifference.pitch / rotationDifference) * turnSpeed.pitchTurnSpeed;
        rotation = clampRotation(Rotation(currentRotation.yaw + U::Math.coerceIn(angleDifference.yaw, -straightLineYaw, straightLineYaw), currentRotation.pitch + U::Math.coerceIn(angleDifference.pitch, -straightLinePitch, straightLinePitch)));
        return rotation;
    }
    void RotationManager::ForceBack()
    {
        this->keepTicks = 0;
    }
    Rotation RotationManager::clampRotation(Rotation rotation)
    {
        // pitch
        rotation.pitch = U::Math.Max(-89.0f, U::Math.Min(89.0f, U::Math.NormalizeAngle(rotation.pitch)));
        // yaw
        rotation.yaw = U::Math.NormalizeAngle(rotation.yaw);
        return rotation;
    }
    Rotation RotationManager::getAngleDifference(Rotation a, Rotation b)
    {
        float yaw = b.yaw - a.yaw;
        float pitch = b.pitch - a.pitch;
        return clampRotation(Rotation(yaw, pitch));
    }
    float RotationManager::computeFactor(float rotationDifference, float turnSpeed)
    {
        // Scale the rotation difference to fit within a reasonable range
        const float scaledDifference = rotationDifference / 120.f;

        // Compute the sigmoid function
        const float sigmoid = 1 / (1 + exp((-steepness * (scaledDifference - midpoint))));

        // Interpolate sigmoid value to fit within the range of turnSpeed
        float interpolatedSpeed = sigmoid * turnSpeed;

        return U::Math.coerceIn(interpolatedSpeed, 0.f, 180.f);
    }
    // TurnSpeed RotationManager::computeTurnSpeed(float distance, float diffH, float diffV, bool crosshair)
    // {
    //     float turnSpeedH = coefDistance * distance + coefDiffH * diffH +
    //                        (crosshair ? coefCrosshairH : 0.f) + interceptH;
    //     float turnSpeedV = coefDistance * distance + coefDiffV * std::max(0.f, diffV - diffH) +
    //                        (crosshair ? coefCrosshairV : 0.f) + interceptV;
    //     return TurnSpeed(std::max(abs(turnSpeedH), minimumTurnSpeedH), std::max(abs(turnSpeedV), minimumTurnSpeedV));
    // }
}