#include "ESPHelper.h"
#include "../../../Manager.h"

namespace F {
	namespace ESPHelperModule {
		inline void drawESP(C_BaseEntity* pBaseEntity, int hit)
		{
			Vector EntityPosition = pBaseEntity->GetBaseAnimating()->GetHitboxPositionByGroup(hit);
			Vector screen;
			int size = 5;
			G::Util.W2S(EntityPosition, screen);
			G::Draw.Line(screen.x, screen.y, screen.x - size, screen.y - size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x, screen.y, screen.x + size, screen.y - size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x, screen.y, screen.x+ size, screen.y+ size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x, screen.y, screen.x- size, screen.y + size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x-size, screen.y-size, screen.x + size, screen.y - size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x+size, screen.y-size, screen.x + size, screen.y + size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x + size, screen.y + size, screen.x - size, screen.y + size, Color(255, 255, 255, 255));
			G::Draw.Line(screen.x - size, screen.y + size, screen.x - size, screen.y - size, Color(255, 255, 255, 255));
			std::string name = "Zombie";
			Color color = Color(255, 255, 255, 255);
			switch (pBaseEntity->GetClientClass()->m_ClassID)
			{
			case EClientClass::Witch:
			{
				name = "Witch";
				color = Color(255, 0, 0, 255);
				break;
			}
			case EClientClass::Tank:
			{
				name = "Tank";
				color = Color(255, 0, 0, 255);
				break;
			}
			case EClientClass::Boomer:
			case EClientClass::Jockey:
			case EClientClass::Smoker:
			case EClientClass::Hunter:
			case EClientClass::Spitter:
			case EClientClass::Charger:
			{
				const char* charPtr = pBaseEntity->GetPlayerName();
				std::string str(charPtr);
				name = "SP Infected " + str;
				color = Color(0, 255, 0, 255);
				break;
			}
			case EClientClass::Infected:
			{
				name = "v";
				break;
			}
			default:
			{
				break;
			}
			}
			G::Draw.String(EFonts::DEBUG, screen.x, screen.y - G::Draw.GetFontHeight(EFonts::DEBUG) - 1, color, TXT_CENTERXY, name.c_str());
		}
		void ESPHelper::onRender2D()
		{
			if (!I::EngineClient->IsInGame() || I::EngineVGui->IsGameUIVisible())
				return;

			const int nLocalIndex = I::EngineClient->GetLocalPlayer();

			C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TerrorPlayer*>();

			if (!pLocal)
				return;
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
					drawESP(pWitch->GetBaseEntity(),HITGROUP_HEAD);
					break;
				}
				case EClientClass::Tank:
				{
					C_Tank* pTank = pEntity->As<C_Tank*>();
					if (!pTank) continue;
					if (pTank->deadflag()) continue;
					drawESP(pTank->GetBaseEntity(), HITGROUP_STOMACH);
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
					drawESP(pPlayer->GetBaseEntity(), hit);
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
					Vector min, max;
					int bone;
					drawESP(pInfected->GetBaseEntity(), HITGROUP_CHEST);

					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
	}
}
