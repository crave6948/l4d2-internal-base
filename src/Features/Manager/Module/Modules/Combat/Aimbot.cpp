#include "Aimbot.h"
#include "random"
#include "../../../RotationManager.h"
namespace F
{
	namespace AimbotModule
	{
		inline IClientEntity *target = nullptr;
		inline Vector targetPosition = Vector();
		inline Vector lastRandom = Vector();
		inline float maxfov = 180.0f, lastTime = 0.0f, lastrndTime = 0.0f;
		inline bool aiming = false, CanAttack = false, IsVisible = false;
		namespace AttackConfig
		{
			bool Slient = true;
			int holdAttackForTick = 0;
			int holdTick = 0;
			float switchTimer = 200, randVecTime = 500;
		}
		namespace RenderLocal
		{
			inline float acceletionList[20] = {0};
			inline int f_i = 0;
			inline bool IsLeftClick = false;
		}
		inline Vector getHitBoxPos(IClientEntity *pEntity, C_TerrorPlayer *pLocal)
		{
			Vector box = Vector();
			ClientClass *pCC = pEntity->GetClientClass();
			Vector vCamera;
			I::EngineClient->GetViewAngles(vCamera);
			switch (pCC->m_ClassID)
			{
			case EClientClass::Tank:
			{
				C_Tank *pPlayer = pEntity->As<C_Tank *>();
				box = pPlayer->GetHitboxPositionByGroup(HITGROUP_CHEST);
				break;
			}
			case EClientClass::Witch:
			{
				C_Witch *pPlayer = pEntity->As<C_Witch *>();
				box = pPlayer->GetHitboxPositionByGroup(HITGROUP_HEAD);
				break;
			}
			case EClientClass::Boomer:
			case EClientClass::Jockey:
			case EClientClass::Smoker:
			case EClientClass::Hunter:
			case EClientClass::Spitter:
			case EClientClass::Charger:
			{
				C_TerrorPlayer *pPlayer = pEntity->As<C_TerrorPlayer *>();
				int hit = HITGROUP_HEAD;
				if (pCC->m_ClassID == EClientClass::Boomer)
				{
					hit = HITGROUP_STOMACH;
				};
				box = pPlayer->GetHitboxPositionByGroup(hit);
				break;
			}
			case EClientClass::Infected:
			{
				C_Infected *pInfected = pEntity->As<C_Infected *>();
				box = pInfected->GetHitboxPositionByGroup(HITGROUP_CHEST);
				break;
			}
			default:
			{
				break;
			}
			}
			if (!box.IsZero())
			{
				if (I::GlobalVars->realtime - lastrndTime >= AttackConfig::randVecTime / 1000)
				{
					lastRandom = Utils::RandomUtils::genVector() * 3.0f;
					lastrndTime = I::GlobalVars->realtime;
				}
				box = box + lastRandom;
				return box;
			}
			return Vector();
		}
		inline bool ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd)
		{
			if (cmd->buttons & IN_USE)
				return false;

			if (pLocal->m_isHangingFromLedge() || pLocal->m_isHangingFromTongue() || !pLocal->CanAttackFull())
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
				target = nullptr;
				aiming = false;
				Helper::rotationManager.ForceBack();
				return;
			}
			bool allowedToSwitch = false;
			if (I::GlobalVars->realtime - lastTime >= AttackConfig::switchTimer / 1000)
			{
				allowedToSwitch = true;
			}
			if (target == nullptr)
			{
				if (allowedToSwitch)
				{
					target = Utils::target.find(pLocal, maxfov);
				}
				if (target == nullptr)
				{
					return;
				}
			}
			else
			{
				bool isDead = Utils::target.CheckInvaidOrDead(pLocal, target);
				if (isDead)
				{
					lastTime = I::GlobalVars->realtime;
					target = nullptr;
					return;
				}
			}
			C_BaseAnimating *pAnimating = target->As<C_BaseAnimating *>();
			Vector destination = getHitBoxPos(target, pLocal);
			if (destination.IsZero())
				return;
			targetPosition = U::Math.GetAngleToPosition(pLocal->Weapon_ShootPosition(), destination);
			Helper::rotationManager.setTargetRotation(targetPosition, 1000);
			aiming = true;
		}
		void Aimbot::onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal)
		{
			CanAttack = pWeapon->CanPrimaryAttack();
			if (!aiming || target == nullptr)
			{
				return;
			}
			if (!AttackConfig::Slient)
			{
				I::EngineClient->SetViewAngles(cmd->viewangles);
			}
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
			IsVisible = shouldhit;
			if (AttackConfig::holdTick > 0)
			{
				AttackConfig::holdTick--;
			}
			if (!CanAttack || !IsVisible)
			{
				if (cmd->buttons & IN_ATTACK && AttackConfig::holdTick <= 0)
				{
					cmd->buttons -= IN_ATTACK;
					RenderLocal::IsLeftClick = cmd->buttons;
				}
				return;
			}
			if (RenderLocal::IsLeftClick && cmd->buttons & IN_ATTACK)
			{
				cmd->buttons -= IN_ATTACK;
				RenderLocal::IsLeftClick = false;
				return;
			}
			cmd->buttons |= IN_ATTACK;
			AttackConfig::holdTick = AttackConfig::holdAttackForTick;
			RenderLocal::IsLeftClick = cmd->buttons;
		}
		inline void acceletionLog(int renderX, int renderY, float acceletion)
		{
			if (RenderLocal::f_i >= 20)
			{
				RenderLocal::f_i = 0;
			}
			RenderLocal::acceletionList[RenderLocal::f_i] = acceletion;
			RenderLocal::f_i++;
			for (int i = 0; i < 20; i++)
			{
				G::Draw.Circle(renderX - 20 + (i * 2), renderY + 15 - (RenderLocal::acceletionList[i]), 1, 8, Color(255, 255, 255, 255));
			}
		}
		void Aimbot::onRender2D()
		{
			int startX = 2, startY = 100;
			if (!I::EngineClient->IsInGame())
			{
				target = nullptr;
				return;
			};
			if (I::EngineVGui->IsGameUIVisible())
			{
				return;
			}
			if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
			{
				AttackConfig::Slient = !AttackConfig::Slient;
			}
			C_TerrorPlayer *pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer *>();
			if (aiming)
			{
				std::string str = "Aiming";
				G::Draw.String(EFonts::DEBUG, startX, startY, Color(255, 255, 255, 255), TXT_DEFAULT, str.c_str());
				startY += G::Draw.GetFontHeight(EFonts::DEBUG) + 1;
				G::Draw.String(EFonts::DEBUG, startX, startY, Color(255, 255, 255, 255), TXT_DEFAULT, ("CanAttack:" + std::to_string(CanAttack)).c_str());
				startY += G::Draw.GetFontHeight(EFonts::DEBUG) + 1;
				G::Draw.String(EFonts::DEBUG, startX, startY, Color(255, 255, 255, 255), TXT_DEFAULT, ("IsVisible:" + std::to_string(IsVisible)).c_str());
				startY += G::Draw.GetFontHeight(EFonts::DEBUG) + 1;
			}
			G::Draw.String(EFonts::DEBUG, startX, startY, Color(255, 255, 255, 255), TXT_DEFAULT, ("IsLeftClick:" + std::to_string(RenderLocal::IsLeftClick)).c_str());
			startY += G::Draw.GetFontHeight(EFonts::DEBUG) + 1;
			if (target != nullptr)
			{
				G::Draw.String(EFonts::DEBUG, startX, startY, Color(255, 255, 255, 255), TXT_DEFAULT, ("Target:" + std::to_string(target->entindex())).c_str());
				startY += G::Draw.GetFontHeight(EFonts::DEBUG) + 1;
				if (!targetPosition.IsZero())
				{
					Vector vec = U::Math.AngleVectors(targetPosition);
					Vector vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * 1400.0f);
					Vector screen;
					G::Util.W2S(vViewAngleOnWorld, screen);
					G::Draw.Line(screen.x, screen.y, screen.x - 4, screen.y - 4, Color(255, 255, 255, 255));
					G::Draw.Line(screen.x, screen.y, screen.x + 4, screen.y - 4, Color(255, 255, 255, 255));
				}
			}
			//(pLocal->IsScoped() && !gVisuals.bNoZoom) ? 30.0f :
			float flR = tanf(DEG2RAD(maxfov) / 2) / tanf(DEG2RAD(110) / 2) * G::Draw.m_nScreenW;
			G::Draw.OutlinedCircle(G::Draw.m_nScreenW / 2, G::Draw.m_nScreenH / 2, flR, 32, Color(178, 190, 181, 255));
		}
		void Aimbot::onEnabled()
		{
			target = nullptr;
		}
		void Aimbot::onDisabled()
		{
		}
	}
}
