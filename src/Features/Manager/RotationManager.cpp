#include "RotationManager.h"
#include "random"
namespace Helper
{
	inline Vector lastRotation = Vector();
	inline float getAngleDifference(float a, float b)
	{
		return (
				   std::fmod(
					   std::fmod(a - b, 360.f) + 540.f, 360.f)) -
			   180.f;
	}
	inline Vector GetLocalViewAngles()
	{
		Vector viewAngles;
		I::EngineClient->GetViewAngles(viewAngles);
		return viewAngles;
	}
	void RotationManager::onUpdate(C_TerrorPlayer *pLocal)
	{
		if (!I::EngineClient->IsInGame()) {
			currentPosition = Vector();
			targetPosition = Vector();
			currentRotation = Vector();
			lastMS = 0;
			keepRotation = 0;
			DisabledRotation = true;
			return;
		}
		if (currentPosition.IsZero())
		{
			Vector vec = U::Math.AngleVectors(GetLocalViewAngles());
			Vector vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * 2.0f);
			currentPosition = vViewAngleOnWorld;
		}
		if (DisabledRotation) { 
			currentRotation = GetLocalViewAngles();
			return;
		}else {
			if (isRotateBack())
			{
				Vector vec = U::Math.AngleVectors(GetLocalViewAngles());
				Vector vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * 2.0f);
				targetPosition = vViewAngleOnWorld;
			}
			calcPosition();
			currentRotation = U::Math.GetAngleToPosition(pLocal->Weapon_ShootPosition(), currentPosition);
			DisabledRotation = ShouldDisabledRotation();
		}
	}
	void RotationManager::setTargetPosition(Vector targetPosition, float keepLength)
	{
		this->targetPosition = targetPosition;
		this->keepRotation = keepLength;
		lastMS = I::GlobalVars->realtime;
		DisabledRotation = false;
	}
	Vector RotationManager::getCurrentRotation()
	{
		return currentRotation;
	}
    float RotationManager::distance(Vector current, Vector target)
    {
        float distanceValue = sqrt(pow(target.x - current.x, 2) + pow(target.y - current.y, 2) + pow(target.z - current.z, 2));
        return distanceValue;
    }
    bool RotationManager::isRotateBack()
    {
        return I::GlobalVars->realtime - lastMS >= keepRotation / 1000;
    }
    bool RotationManager::ShouldDisabledRotation()
    {
        if (!isRotateBack()) return false;
		return DisabledRotation || distance(currentPosition, targetPosition) <= 1;
    }
    void RotationManager::calcPosition()
    {
		Vector diffPosition = targetPosition - currentPosition;
		currentPosition += diffPosition / 2;
	}
}
