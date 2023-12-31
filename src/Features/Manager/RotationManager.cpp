#include "RotationManager.h"
#include "random"
namespace Helper
{
	inline Vector lastRotation = Vector();
	inline float lastStartedMS = 0;
	inline Vector GetLocalViewAngles()
	{
		Vector viewAngles;
		I::EngineClient->GetViewAngles(viewAngles);
		return viewAngles;
	}
	float easeInOutQuint(float t)
	{
		if (t < 0.5)
		{
			return 16 * pow(t, 5);
		}
		else
		{
			return 1 + 16 * pow(t - 1, 5);
		}
	}
	void RotationManager::onUpdate(C_TerrorPlayer *pLocal)
	{
		if (!I::EngineClient->IsInGame())
		{
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
			if (!targetPosition.IsZero()) {
				Vector vtest = pLocal->Weapon_ShootPosition() + (vec * 1400.0f);
				float v1 = distance(vtest, pLocal->Weapon_ShootPosition());
				float v2 = distance(vtest, targetPosition);
				if (v2 > v1) {
					vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * distance(pLocal->Weapon_ShootPosition(), targetPosition));
				}
			}
			currentPosition = vViewAngleOnWorld;
		}
		if (DisabledRotation)
		{
			targetPosition = Vector();
			currentPosition = Vector();
			currentRotation = GetLocalViewAngles();
			lastMS = 0;
			keepRotation = 0;
			return;
		}
		else
		{
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
		if (this->targetPosition.IsZero())
			lastStartedMS = I::GlobalVars->realtime;
		this->targetPosition = targetPosition;
		this->keepRotation = keepLength;
		lastMS = I::GlobalVars->realtime;
		DisabledRotation = false;
	}
	void RotationManager::ForceBack()
	{
		lastMS = keepRotation / 1000;
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
		if (!isRotateBack())
			return false;
		return DisabledRotation || distance(currentPosition, targetPosition) <= 1;
	}
	void RotationManager::calcPosition()
	{
		Vector diffPosition = targetPosition - currentPosition;
		float startTime = lastStartedMS;
		float endInTime = lastStartedMS + 1000;
		float converted = 1 + ((endInTime - startTime) / 1000);//convert in to scale from 0 to 1;
		float easedValue = easeInOutQuint(converted);
		currentPosition = currentPosition + (diffPosition * easedValue);
		if (distance(currentPosition, targetPosition) <= 1) {
			lastStartedMS = I::GlobalVars->realtime;
		}
	}
}
