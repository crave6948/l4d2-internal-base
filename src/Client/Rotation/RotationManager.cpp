#include "RotationManager.h"

#include "../None.h"
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
                if (rotationDifference <= 0.1f)
                    DisabledRotation = true;
            }
            else if (forceFocus <= 0)
            {
                const auto rotations = Client::client.moduleManager.rotations;
                serverRotation = calculateRotation(serverRotation, targetRotation, targetDistance, isInCrosshair);
                float rotationDifference = U::Math.GetFovBetween(serverRotation.toVector(), targetRotation.toVector());
                if (rotationDifference <= 0.1f && isInCrosshair)
                    forceFocus = rotations->ForceFocusTicks->GetValue();
            }
            if (forceFocus > 0) forceFocus--;
            ticksToRotate = TIME_TO_TICKS(0.01);
        }
    }
    Rotation RotationManager::calculateRotation(Rotation currentRotation, Rotation targetRotation, float targetdistance = 0.f, bool isInCrosshair = false)
    {
        Rotation angleDifference = getAngleDifference(currentRotation, targetRotation);
        float rotationDifference = U::Math.GetFovBetween(currentRotation.toVector(), targetRotation.toVector());
        const auto rotations = Client::client.moduleManager.rotations;
        TurnSpeed turnSpeed;
        float straightLineYaw;
        float straightLinePitch;
        if (rotations->rotationModes->GetSelected() == "Linear")
        {
            auto [minH, maxH] = rotations->linear_horizontalTurnSpeed->GetValue();
            auto [minV, maxV] = rotations->linear_verticalTurnSpeed->GetValue();
            float randomYaw = nextGassain(minH, maxH);
            float randomPitch = nextGassain(minV, maxV);

            straightLineYaw = abs(angleDifference.yaw / rotationDifference) * randomYaw;
            straightLinePitch = abs(angleDifference.pitch / rotationDifference) * randomPitch;
        }
        if (rotations->rotationModes->GetSelected() == "Conditional")
        {
            // get turnspeed from computeTurnSpeed function
            turnSpeed = this->computeTurnSpeed(
                targetdistance,
                abs(angleDifference.yaw),
                abs(angleDifference.pitch),
                isInCrosshair);
            straightLineYaw = std::max(abs(angleDifference.yaw / rotationDifference) * turnSpeed.yawTurnSpeed, rotations->minimumTurnSpeedH->GetValue());
            straightLinePitch = std::max(abs(angleDifference.pitch / rotationDifference) * turnSpeed.pitchTurnSpeed, rotations->minimumTurnSpeedV->GetValue());
        }
        if (rotations->rotationModes->GetSelected() == "Sigmoid")
        {
            // random horizontal and vertical turnspeeds
            auto [minH, maxH] = rotations->sigmoid_horizontalTurnSpeed->GetValue();
            auto [minV, maxV] = rotations->sigmoid_verticalTurnSpeed->GetValue();
            float randomYaw = nextGassain(minH, maxH);
            float randomPitch = nextGassain(minV, maxV);

            turnSpeed = TurnSpeed(computeFactor(rotationDifference, randomYaw), computeFactor(rotationDifference, randomPitch));
            straightLineYaw = abs(angleDifference.yaw / rotationDifference) * turnSpeed.yawTurnSpeed;
            straightLinePitch = abs(angleDifference.pitch / rotationDifference) * turnSpeed.pitchTurnSpeed;
        }
        Rotation rotation = clampRotation(Rotation(currentRotation.yaw + U::Math.coerceIn(angleDifference.yaw, -straightLineYaw, straightLineYaw), currentRotation.pitch + U::Math.coerceIn(angleDifference.pitch, -straightLinePitch, straightLinePitch)));
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
        const auto rotations = Client::client.moduleManager.rotations;
        // Scale the rotation difference to fit within a reasonable range
        const float scaledDifference = rotationDifference / 120.f;

        // Compute the sigmoid function
        const float sigmoid = 1 / (1 + exp((-rotations->steepness->GetValue() * (scaledDifference - rotations->midpoint->GetValue()))));

        // Interpolate sigmoid value to fit within the range of turnSpeed
        float interpolatedSpeed = sigmoid * turnSpeed;

        return U::Math.coerceIn(interpolatedSpeed, 0.f, 180.f);
    }
    TurnSpeed RotationManager::computeTurnSpeed(float distance, float diffH, float diffV, bool crosshair)
    {
        const auto rotations = Client::client.moduleManager.rotations;
        float turnSpeedH = rotations->coefDistance->GetValue() * distance + rotations->coefDiffH->GetValue() * diffH +
                           (crosshair ? rotations->coefCrosshairH->GetValue() : 0.f) + rotations->interceptH->GetValue();
        float turnSpeedV = rotations->coefDistance->GetValue() * distance + rotations->coefDiffV->GetValue() * std::max(0.f, diffV - diffH) +
                           (crosshair ? rotations->coefCrosshairV->GetValue() : 0.f) + rotations->interceptV->GetValue();
        return TurnSpeed(std::max(abs(turnSpeedH), rotations->minimumTurnSpeedH->GetValue()), std::max(abs(turnSpeedV), rotations->minimumTurnSpeedV->GetValue()));
    }
}