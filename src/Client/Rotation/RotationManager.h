#pragma once
#include "../../SDK/SDK.h"
namespace Helper
{
	class RotationManager
	{
	public:
		Vector current = Vector(), target = Vector();
		float keepRotation = 0;
		float lastMS = 0;
		bool DisabledRotation = true;
		void ForceBack();
		void onUpdate(C_TerrorPlayer* pLocal);
		void setTargetRotation(Vector rotation, float keepLength);
		Vector getCurrentRotation();
	private:
		bool ShouldDisabledRotation();
		bool calcRotation(float lastdist);
		bool hasKeepRotationReachedLimit();
		float calculateRealisticTurnSpeed(float rotationDiff, float supposedTurnSpeed);
		float calculateTurnSpeedWithCurve(float rotationDiff);
		void clampRotation(Vector& diffRotation, float realisticTurnSpeed);
	};
	inline RotationManager rotationManager = RotationManager();
}