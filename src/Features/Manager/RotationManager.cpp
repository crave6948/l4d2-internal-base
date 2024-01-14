#include "RotationManager.h"
#include "random"
namespace Helper {
	inline Vector lastSetTarget = Vector();
	inline float lastdist = -1;
	inline double nextGassain( double min, double max) {
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution(min, max);
		return distribution(generator);
	}
	inline float getAngleDifference(float a, float b)
	{
		return (
				std::fmod(
					std::fmod(a - b, 360.f) + 540.f, 360.f)) -
			180.f;
	}

	inline bool is_lac_detected(float aimdist, float laimdist, float tdelta) {
		if (laimdist == -1) {
			return false;
		}
		bool detected = false;
		// Check conditions for AIMBOT_FLAG_SNAP
		if (aimdist < laimdist * 0.2 && tdelta > 10.0)
			detected |= true;

		// Check conditions for AIMBOT_FLAG_SNAP2
		if (aimdist < laimdist * 0.1 && tdelta > 5.0)
			detected |= true;
		return detected;
	}

	bool RotationManager::hasKeepRotationReachedLimit()
	{
		return I::GlobalVars->realtime - lastMS >= keepRotation / 1000;
	}

	bool RotationManager::ShouldDisabledRotation()
	{
		if (!hasKeepRotationReachedLimit())
			return false;
		return DisabledRotation || U::Math.GetFovBetween(current, target) <= 1;
	}
	bool RotationManager::calcRotation(float lastdist)
	{
		if (DisabledRotation)
		{
			lastdist = -1;
			return true;
		}

		Vector diffRotation = target - current;
		U::Math.ClampAngles(diffRotation);
		float rotationDiff = U::Math.GetFovBetween(current, target);
		
		float supposedTurnSpeed = nextGassain(65.0, 180.0);
		float realisticTurnSpeed = calculateRealisticTurnSpeed(rotationDiff, supposedTurnSpeed);

		if (rotationDiff > 30)
		{
			realisticTurnSpeed = calculateTurnSpeedWithCurve(rotationDiff);
		}

		realisticTurnSpeed = round(realisticTurnSpeed * 100.0f) / 100.0f;
		clampRotation(diffRotation, realisticTurnSpeed);
		
		Vector pre = current;
		U::Math.ClampAngles(diffRotation);
		current += diffRotation;
		U::Math.ClampAngles(current);

		float aimdist = U::Math.GetFovBetween(pre, current);

		if (is_lac_detected(aimdist, lastdist, rotationDiff))
		{
			return false;
		}

		lastdist = aimdist;
		return true;
	}

	float RotationManager::calculateRealisticTurnSpeed(float rotationDiff, float supposedTurnSpeed)
	{
		return rotationDiff * (rotationDiff <= 5 ? std::max(0.3f, supposedTurnSpeed / 180.0f) : (supposedTurnSpeed / 180.0f));
	}

	float RotationManager::calculateTurnSpeedWithCurve(float rotationDiff)
	{
		float a1 = (-cos(rotationDiff / 180.f * M_PI) * 0.5f + 0.5f);
		float a2 = (1.f - (-cos(rotationDiff / 180.f * M_PI) * 0.5f + 0.5f));
		return pow(a1, 2.0f) * nextGassain(115.0, 135.0) + pow(a2, 2.0f) * nextGassain(10.0, 15.0);
	}

	void RotationManager::clampRotation(Vector& diffRotation, float realisticTurnSpeed)
	{
		diffRotation.x = std::clamp(diffRotation.x, -realisticTurnSpeed, realisticTurnSpeed);
		diffRotation.y = std::clamp(diffRotation.y, -realisticTurnSpeed, realisticTurnSpeed);
	}

	void RotationManager::ForceBack()
	{
		keepRotation = 500;
	}
	void RotationManager::onUpdate(C_TerrorPlayer *pLocal)
	{
		if (!I::EngineClient->IsInGame())
		{
			current = Vector();
			target = Vector();
			keepRotation = 0;
			lastdist = -1;
			DisabledRotation = true;
			return;
		}

		Vector viewAngles;
		I::EngineClient->GetViewAngles(viewAngles);
		if (current.IsZero())
		{
			current = viewAngles;
			return;
		}
		if (hasKeepRotationReachedLimit())
		{
			target = viewAngles;
		}
		bool passed = false;
		while (passed == false)
		{
			passed = calcRotation(lastdist);
		}
		DisabledRotation = ShouldDisabledRotation();
		if (DisabledRotation)
		{
			current = viewAngles;
			return;
		}
	}

	void RotationManager::setTargetRotation(Vector rotation, float keepLength)
	{
		if (lastSetTarget.IsZero()) {
			lastSetTarget = rotation;
		}else {
			if (U::Math.GetFovBetween(lastSetTarget, rotation) > 10) {
				lastdist = -1;
			}
		}
		target = rotation;
		lastMS = I::GlobalVars->realtime;
		keepRotation = keepLength;
		DisabledRotation = false;
	}

	Vector RotationManager::getCurrentRotation()
	{
		return current;
	}
}