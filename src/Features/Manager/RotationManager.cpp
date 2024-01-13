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
		return DisabledRotation || hypot(getAngleDifference(target.y, current.y), target.x - current.x) <= 1;
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
		
		float supposedTurnSpeed = nextGassain(65.0,180.0);
		float realisticTurnSpeed = rotationDiff * (rotationDiff <= 7 ? U::Math.Max(0.5f, supposedTurnSpeed / 180.0f) : (supposedTurnSpeed / 180.0f));
		if (rotationDiff > 30)
		{
			float a1 = (-cos(rotationDiff / 180.f * M_PI) * 0.5f + 0.5f);
			float a2 = (1.f - (-cos(rotationDiff / 180.f * M_PI) * 0.5f + 0.5f));
			realisticTurnSpeed = pow(a1, 2.0f) * nextGassain(30.0,40.0) + pow(a2, 2.0f) * nextGassain(7.0, 17.0);
		}
		if (diffRotation.x > realisticTurnSpeed)
		{
			diffRotation.x = realisticTurnSpeed;
		}
		else
		{
			diffRotation.x = U::Math.Max(diffRotation.x, -realisticTurnSpeed);
		}
		if (diffRotation.y > realisticTurnSpeed)
		{
			diffRotation.y = realisticTurnSpeed;
		}
		else
		{
			diffRotation.y = U::Math.Max(diffRotation.y, -realisticTurnSpeed);
		}
		Vector pre = current;
		U::Math.ClampAngles(diffRotation);
		current = current + diffRotation;
		U::Math.ClampAngles(current);
		float aimdist = pre.DistTo(current);
		if (is_lac_detected(aimdist,lastdist,rotationDiff)) {
			return false;
		}
		lastdist = aimdist;
		return true;
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
			if (lastSetTarget.DistTo(rotation) > 130) {
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