#pragma once
#include "../../../../SDK/SDK.h"

namespace Utils
{
	class FindTarget
	{
	public:
		Vector serverRotation = Vector();
		bool CheckInvaidOrDead(C_TerrorPlayer* pLocal, IClientEntity* target);
		IClientEntity* find(C_TerrorPlayer* pLocal, float maxfov);
	private:
		float maxfov = 999.f;
		float getScore(C_BaseAnimating* pAnimating, IClientEntity* pEntity, C_TerrorPlayer* pLocal, int hitgroup);
	};
}
