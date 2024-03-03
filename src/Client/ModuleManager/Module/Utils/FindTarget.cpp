#include "FindTarget.h"
namespace Utils
{
	inline float FindTarget::getScore(C_BaseAnimating* pAnimating, IClientEntity* pEntity, C_TerrorPlayer* pLocal, int hitgroup) {
		float score = -1;
		Vector entityposition;
		if (!pAnimating->GetHitboxPositionByGroup(hitgroup, entityposition))
		{
			return -1;
		}
		Vector LocalPlayerPosition = pLocal->Weapon_ShootPosition();
		float distance = LocalPlayerPosition.DistTo(entityposition);
		if (distance <= 1400)
		{
			CTraceFilterHitscan filter{ pLocal };
			auto pHit{ G::Util.GetHitEntity(LocalPlayerPosition, entityposition, &filter) };
			if (!pHit || pHit->entindex() != pEntity->entindex()) return -1;
			Vector vCamera;
			I::EngineClient->GetViewAngles(vCamera);
			float fov = U::Math.GetFovBetween(!serverRotation.IsZero() ? serverRotation : vCamera, U::Math.GetAngleToPosition(LocalPlayerPosition, entityposition));
			if (fov > maxfov) return -1;
			float distancepercent = (distance * 100) / 1400;
			float fovpercent = (fov * 100) / maxfov;
			score = 100 - fovpercent;
		}
		return score;
	}
	bool FindTarget::CheckInvaidOrDead(C_TerrorPlayer* pLocal, IClientEntity* target)
	{
		if (!target) return false;
		int hit = HITGROUP_HEAD;
		ClientClass* pCC = target->GetClientClass();
		if (!pCC)
			return true;
		switch (pCC->m_ClassID)
		{
		case EClientClass::Witch:
		{
			C_Witch* pWitch = target->As<C_Witch*>();
			if (!pWitch) return true;
			if (!G::Util.IsInfectedAlive(pWitch->m_usSolidFlags(), pWitch->m_nSequence()))
			{
				return true;
			}
			break;
		}
		case EClientClass::Tank:
		{
			hit = HITGROUP_STOMACH;
			C_Tank* pTank = target->As<C_Tank*>();
			if (!pTank) return true;
			if (pTank->deadflag()) return true;
			break;
		}
		case EClientClass::Boomer:
		case EClientClass::Jockey:
		case EClientClass::Smoker:
		case EClientClass::Hunter:
		case EClientClass::Spitter:
		case EClientClass::Charger:
		{
			if (pCC->m_ClassID == EClientClass::Boomer) { hit = HITGROUP_STOMACH; };
			C_TerrorPlayer* pPlayer = target->As<C_TerrorPlayer*>();
			if (!pPlayer) return true;
			if (pPlayer->deadflag()) return true;
			break;
		}
		case EClientClass::Infected:
		{
			hit = HITGROUP_STOMACH;
			C_Infected* pInfected = target->As<C_Infected*>();
			if (!pInfected) return true;
			if (!G::Util.IsInfectedAlive(pInfected->m_usSolidFlags(), pInfected->m_nSequence()) || pInfected->m_bIsBurning())
			{
				return true;
			}
			break;
		}
		default:
			break;
		}
		C_BaseAnimating* pAnimating = target->As<C_BaseAnimating*>();
		Vector entityposition;
		if (!pAnimating->GetHitboxPositionByGroup(hit, entityposition))
		{
			return true;
		}
		Vector LocalPlayerPosition = pLocal->Weapon_ShootPosition();
		float distance = LocalPlayerPosition.DistTo(entityposition);
		if (distance > 1400) return true;
		CTraceFilterWorldAndPropsOnly filter;
		if (!G::Util.IsVisible(LocalPlayerPosition, entityposition, &filter)) return true;
		Vector vCamera;
		I::EngineClient->GetViewAngles(vCamera);
		float fov = U::Math.GetFovBetween(vCamera, U::Math.GetAngleToPosition(LocalPlayerPosition, entityposition));
		if (fov > maxfov + 15.0f) return true;
		return false;
	}
	IClientEntity* FindTarget::find(C_TerrorPlayer* pLocal, float fov)
	{
		maxfov = fov;
		IClientEntity* bestTarget = nullptr;
		float bestscore = 0;
		const int nLocalIndex = I::EngineClient->GetLocalPlayer();
		for (int n = 1; n < (I::ClientEntityList->GetMaxEntities() + 1); n++)
		{
			if (n == nLocalIndex)
				continue;

			IClientEntity* pEntity = I::ClientEntityList->GetClientEntity(n);

			if (!pEntity || pEntity->IsDormant())
				continue;

			ClientClass* pCC = pEntity->GetClientClass();

			if (!pCC)
				continue;

			switch (pCC->m_ClassID)
			{
			case EClientClass::Witch:
			{
				C_Witch* pWitch = pEntity->As<C_Witch*>();
				if (!pWitch) continue;
				if (!G::Util.IsInfectedAlive(pWitch->m_usSolidFlags(), pWitch->m_nSequence()))
				{
					continue;
				}
				if (pWitch->m_rage() != 1.0f)
				{
					continue;
				}
				C_BaseAnimating* pAnimating = pEntity->As<C_BaseAnimating*>();
				float thisscore = getScore(pAnimating, pEntity, pLocal, HITGROUP_HEAD);
				if (bestscore > thisscore) {
					continue;
				}
				bestscore = thisscore;
				bestTarget = pEntity;
				break;
			}
			case EClientClass::Tank:
			{
				C_Tank* pTank = pEntity->As<C_Tank*>();
				if (!pTank) continue;
				if (pTank->deadflag()) continue;
				C_BaseAnimating* pAnimating = pEntity->As<C_BaseAnimating*>();
				float thisscore = getScore(pAnimating, pEntity, pLocal, HITGROUP_STOMACH);
				if (bestscore > thisscore) {
					continue;
				}
				bestscore = thisscore;
				bestTarget = pEntity;
				break;
			}
			case EClientClass::Boomer:
			case EClientClass::Jockey:
			case EClientClass::Smoker:
			case EClientClass::Hunter:
			case EClientClass::Spitter:
			case EClientClass::Charger:
			{
				C_TerrorPlayer* pPlayer = pEntity->As<C_TerrorPlayer*>();
				if (!pPlayer) continue;
				if (pPlayer->deadflag())
				{
					continue;
				}
				C_BaseAnimating* pAnimating = pEntity->As<C_BaseAnimating*>();
				int hit = HITGROUP_HEAD;
				if (pCC->m_ClassID == EClientClass::Boomer) { hit = HITGROUP_STOMACH; };
				float thisscore = getScore(pAnimating, pEntity, pLocal, hit);
				if (bestscore > thisscore) {
					continue;
				}
				bestscore = thisscore;
				bestTarget = pEntity;
				break;
			}
			case EClientClass::Infected:
			{
				C_Infected* pInfected = pEntity->As<C_Infected*>();
				if (!pInfected) continue;
				if (!G::Util.IsInfectedAlive(pInfected->m_usSolidFlags(), pInfected->m_nSequence()) || pInfected->m_bIsBurning())
				{
					continue;
				}
				C_BaseAnimating* pAnimating = pEntity->As<C_BaseAnimating*>();
				float thisscore = getScore(pAnimating, pEntity, pLocal, HITGROUP_STOMACH);
				if (bestscore > thisscore) {
					continue;
				}
				bestscore = thisscore;
				bestTarget = pEntity;
				break;
			}
			default:
			{
				break;
			}
			}
		}
		return bestTarget;
	}
}