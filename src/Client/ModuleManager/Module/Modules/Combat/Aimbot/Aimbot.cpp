#include "Aimbot.h"
#include "../../../../../Rotation/RotationManager.h"
#include <functional>

namespace Client::Module::AimbotModule
{
	bool Aimbot::ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd)
	{
		if (!I::EngineClient->IsInGame())
		{
			return false;
		}
		if (I::EngineVGui->IsGameUIVisible())
		{
			return false;
		}

		if (cmd->buttons & IN_USE)
			return false;

		if (pLocal->m_isHangingFromLedge() || pLocal->m_isHangingFromTongue() || pLocal->m_isIncapacitated())
			return false;

		// You could also check if the current spread is -1.0f and not run nospread I guess.
		// But since I wanted to filter out shotungs and just be sure that it isnt ran for other stuff I check the weaponid.
		if (!pWeapon)
			return false;
		switch (pWeapon->GetWeaponID())
		{
		case WEAPON_AK47:
		case WEAPON_AWP:
		case WEAPON_DEAGLE:
		case WEAPON_HUNTING_RIFLE:
		case WEAPON_M16A1:
		case WEAPON_M60:
		case WEAPON_MAC10:
		case WEAPON_MILITARY_SNIPER:
		case WEAPON_MP5:
		case WEAPON_PISTOL:
		case WEAPON_SCAR:
		case WEAPON_SCOUT:
		case WEAPON_SSG552:
		case WEAPON_UZI:
		case WEAPON_AUTO_SHOTGUN:
		case WEAPON_SPAS:
		case WEAPON_PUMP_SHOTGUN:
		case WEAPON_CHROME_SHOTGUN:
			return true;
		default:
			break;
		}

		return false;
	}
	void Aimbot::onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
	{
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000) || !ShouldRun(pLocal, pWeapon, cmd))
		{
			targetInfo = TargetInfo();
			Helper::rotationManager.ForceBack();
			return;
		}
		if (lastSwitchTime >= TIME_TO_TICKS(switchDelay->GetValue() / 1000)) {
			targetInfo = TargetInfo();
			targetInfo = GetTarget(pLocal, pWeapon, cmd);
			lastSwitchTime = 0;
		}else {
			lastSwitchTime++;
		}
		if (targetInfo.target == nullptr) return;
		float distance = pLocal->Weapon_ShootPosition().DistTo(targetInfo.targetPosition);
		bool isInCrosshair = isInCrossHair(cmd, pLocal, targetInfo.target);
		Helper::rotationManager.moveTo(targetInfo.aimRotation,distance, isInCrosshair);

		if (cmd->buttons & IN_ATTACK)
		{
			if (!isInCrosshair) {
				cmd->buttons &= ~IN_ATTACK;
			}
		}
	}
	void Aimbot::onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
	{
		if (!silent->GetValue())
		{
			I::EngineClient->SetViewAngles(cmd->viewangles);
		}
	}
	void Aimbot::onRender2D()
	{
		int startX = 2, startY = 100;
		if (!I::EngineClient->IsInGame())
		{
			return;
		};
		if (I::EngineVGui->IsGameUIVisible())
		{
			return;
		}
		C_TerrorPlayer *pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer *>();
		float flR = tanf(DEG2RAD(fov->GetValue()) / 2) / tanf(DEG2RAD(pLocal->IsZoomed() ? 30 : 110) / 2) * G::Draw.m_nScreenW;
		G::Draw.OutlinedCircle(G::Draw.m_nScreenW / 2, G::Draw.m_nScreenH / 2, flR, 32, Color(178, 190, 181, 255));
		if (!debug->GetValue())
			return;
		//(pLocal->IsScoped() && !gVisuals.bNoZoom) ? 30.0f :
	}
	void Aimbot::onEnabled()
	{
		targetInfo = TargetInfo();
		lastSwitchTime = 0;
	}
	void Aimbot::onDisabled()
	{
	}
	bool Aimbot::isInCrossHair(CUserCmd *cmd, C_TerrorPlayer *pLocal, IClientEntity *target)
	{
		Vector vec = U::Math.AngleVectors(cmd->viewangles);
		CTraceFilterHitscan filter{pLocal};
		bool shouldhit = false;
		if (auto pHit = G::Util.GetHitEntity(pLocal->Weapon_ShootPosition(), pLocal->Weapon_ShootPosition() + (vec * 1400.f), &filter))
		{
			if (pHit->entindex() != target->entindex())
			{
				switch (pHit->GetClientClass()->m_ClassID)
				{
				case EClientClass::Infected:
				case EClientClass::Boomer:
				case EClientClass::Jockey:
				case EClientClass::Smoker:
				case EClientClass::Hunter:
				case EClientClass::Spitter:
				case EClientClass::Charger:
				case EClientClass::Tank:
				{
					shouldhit = true;
					break;
				}
				case EClientClass::Witch:
				{
					shouldhit = true;
					if (pHit->As<C_Witch *>()->m_rage() != 1.0f)
					{
						shouldhit = false;
					}
					break;
				}
				default:
					break;
				}
			}
			else
			{
				shouldhit = true;
			}
		}
		return shouldhit;
	}
	TargetInfo Aimbot::GetTarget(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd)
	{
		Utils::g_EntityCache.update();
		IClientEntity *foundTarget = nullptr;
		// collect all targets and find the best one (compare them by a score)
		Vector clientViewAngles = Helper::rotationManager.getServerRotationVector();
		if (Helper::rotationManager.DisabledRotation)
			I::EngineClient->GetViewAngles(clientViewAngles);
		float currentScore = 2.f;
		int type = HITGROUP_HEAD;
		const auto updateTarget = [&](IClientEntity *target, float fov, float distance) -> bool {
			float fovScore = fov / this->fov->GetValue();
			float distanceScore = distance / this->range->GetValue();
			float score = fovScore + distanceScore;
			if (score < currentScore) {
				foundTarget = target;
                currentScore = score;
				return true;
			}
			return false;
		};
		const auto GetHitbox = [&](int classType) -> int
		{
			if (classType == EClientClass::Tank)
			{
				return HITGROUP_CHEST;
			}
			return HITGROUP_HEAD;
		};
		const auto GetFovDistance = [&, clientViewAngles](IClientEntity *target, int classType) -> std::pair<float, float>
		{
			Vector src = pLocal->Weapon_ShootPosition();
			Vector dst = target->As<C_BaseAnimating*>()->GetHitboxPositionByGroup(GetHitbox(classType));
			float distance = src.DistTo(dst);
			
			float fov = U::Math.GetFovBetween(clientViewAngles, U::Math.GetAngleToPosition(src, dst));
			return std::make_pair(fov, distance);
		};
		const auto doCompare = [&](IClientEntity *target, int classType) -> void {
			if (foundTarget == nullptr) {
				foundTarget = target;
				return;
			}
			auto [fov, distance] = GetFovDistance(target, classType);
			if (updateTarget(target, fov, distance)) {
				type = classType;
			}
		};
		const auto checkCondition = [&](IClientEntity *target, int classType) -> bool {
			auto [fov, distance] = GetFovDistance(target, classType);
			if (distance > this->range->GetValue()) return false;
			if (fov > this->fov->GetValue()) return false;

			Vector hitbox = target->As<C_BaseAnimating*>()->GetHitboxPositionByGroup(GetHitbox(classType));
			CTraceFilterHitAll filter;
			bool isVisible = G::Util.IsVisible(pLocal->Weapon_ShootPosition(), hitbox, &filter);
			return isVisible;
		};
		for (auto &[enabled, classType] : entityTypes)
		{
			if (enabled())
			{
				for (auto entity : Utils::g_EntityCache.getEntityFromGroup(classType))
				{
					if (!checkCondition(entity, classType)) continue;
					doCompare(entity, classType);
				}
			}
		}
		if (foundTarget == nullptr) return TargetInfo();
		Vector hitbox = foundTarget->As<C_BaseAnimating*>()->GetHitboxPositionByGroup(GetHitbox(type));
		Vector aimVector = U::Math.GetAngleToPosition(pLocal->Weapon_ShootPosition(), hitbox);
		return TargetInfo(foundTarget, hitbox, Helper::Rotation().toRotation(aimVector), type);
	}
}