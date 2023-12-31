#pragma once
#include "../../SDK/SDK.h"
namespace Helper
{
	class RotationManager
	{
	public:
		void onUpdate(C_TerrorPlayer* pLocal);
		void setTargetPosition(Vector targetPosition, float keepLength);
		Vector getCurrentRotation();
		bool DisabledRotation = false;
	private:
		float lastMS = 0, keepRotation = 0;
		float distance(Vector current, Vector target);
		bool isRotateBack();
		bool ShouldDisabledRotation();
		void calcPosition();
		Vector currentRotation = Vector();
		Vector currentPosition = Vector(), targetPosition = Vector();
	};
	inline RotationManager rotationManager = RotationManager();
}