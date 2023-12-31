#include "RotationManager.h"
#include "random"
namespace Helper
{
	inline Vector GetLocalViewAngles()
	{
		Vector viewAngles;
		I::EngineClient->GetViewAngles(viewAngles);
		return viewAngles;
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
					vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * std::min(200.f,distance(pLocal->Weapon_ShootPosition(), targetPosition)));
				}
			}
			currentPosition = vViewAngleOnWorld;
		}
		if (DisabledRotation)
		{
			currentRotation = GetLocalViewAngles();
			Vector vec = U::Math.AngleVectors(GetLocalViewAngles());
			Vector vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * 2.0f);
			currentPosition = vViewAngleOnWorld;
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
		float d = distance(targetPosition, currentPosition);
		float a1 = (-cos(d / 700.f * M_PI) * 0.5f + 0.5f);
		float a2 = (1.f - (-cos(d / 700.f * M_PI) * 0.5f + 0.5f));
		float realisticTurnSpeed = realisticTurnSpeed = static_cast<float>(pow(a1, 2.0)) * 200 + static_cast<float>(pow(a2, 2.0)) * 10;

		if (diffPosition.x > realisticTurnSpeed)
		{
			diffPosition.x = realisticTurnSpeed;
		}
		else {
			diffPosition.x = U::Math.Max(diffPosition.x, -realisticTurnSpeed);
		}
		if (diffPosition.y > realisticTurnSpeed)
		{
			diffPosition.y = realisticTurnSpeed;
		}
		else {
			diffPosition.y = U::Math.Max(diffPosition.y, -realisticTurnSpeed);
		}
		if (diffPosition.z > realisticTurnSpeed)
		{
			diffPosition.z = realisticTurnSpeed;
		}
		else {
			diffPosition.z = U::Math.Max(diffPosition.z, -realisticTurnSpeed);
		}
		currentPosition = currentPosition + diffPosition;
	}
}
