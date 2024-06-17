#include "ESPHelper.h"

#include "../../../../None.h"
namespace Client::Module
{
	namespace ESPHelperModule
	{
		void ESPHelper::drawESP(C_BaseEntity *pBaseEntity, int hit)
		{
			const int nLocalIndex = I::EngineClient->GetLocalPlayer();
			C_TerrorPlayer *pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TerrorPlayer *>();

			Vector EntityPosition = pBaseEntity->GetBaseAnimating()->GetHitboxPositionByGroup(hit);
			Color boxColor = Color(255, 255, 255, 255);
			auto aimbot = Client::client.moduleManager.aimbot;
			IClientEntity *target = aimbot->targetInfo.target;

			float distance = pLocal->Weapon_ShootPosition().DistTo(EntityPosition);
			if (distance <= aimbot->range->GetValue())
			{
				auto [r, g, b, a] = this->aimbotInRangeColor->GetValue();
				int alpha = round(a * 255);
				boxColor = Color(r, g, b, alpha);
			}

			if (target != nullptr)
			{
				if (target->entindex() == pBaseEntity->entindex()) {
					auto [r, g, b, a] = this->aimbotColor->GetValue();
					int alpha = round(a * 255);
					boxColor = Color(r, g, b, alpha);
				}
			}
			
			Vector screen;
			int size = 6;
			G::Util.W2S(EntityPosition, screen);
			// G::Draw.Line(screen.x - size / 2, screen.y - size / 2, screen.x - size, screen.y - size, boxColor);
			// G::Draw.Line(screen.x + size / 2, screen.y - size / 2, screen.x + size, screen.y - size, boxColor);
			// G::Draw.Line(screen.x + size / 2, screen.y + size / 2, screen.x + size, screen.y + size, boxColor);
			// G::Draw.Line(screen.x - size / 2, screen.y + size / 2, screen.x - size, screen.y + size, boxColor);
			// G::Draw.Line(screen.x - size, screen.y - size, screen.x + size, screen.y - size, boxColor);
			// G::Draw.Line(screen.x + size, screen.y - size, screen.x + size, screen.y + size, boxColor);
			// G::Draw.Line(screen.x + size, screen.y + size, screen.x - size, screen.y + size, boxColor);
			// G::Draw.Line(screen.x - size, screen.y + size, screen.x - size, screen.y - size, boxColor);
			const int half = size / 2;
			// top left corner
			G::Draw.Line(screen.x - size, screen.y - size, screen.x - half, screen.y - size, boxColor);
			G::Draw.Line(screen.x - size, screen.y - size, screen.x - size, screen.y - half, boxColor);
			// top right corner
			G::Draw.Line(screen.x + size, screen.y - size, screen.x + half, screen.y - size, boxColor);
            G::Draw.Line(screen.x + size, screen.y - size, screen.x + size, screen.y - half, boxColor);
            // bottom left corner
            G::Draw.Line(screen.x - size, screen.y + size, screen.x - half, screen.y + size, boxColor);
            G::Draw.Line(screen.x - size, screen.y + size, screen.x - size, screen.y + half, boxColor);
            // bottom right corner
            G::Draw.Line(screen.x + size, screen.y + size, screen.x + half, screen.y + size, boxColor);
			G::Draw.Line(screen.x + size, screen.y + size, screen.x + size, screen.y + half, boxColor);
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
				name = "Boomer";
				color = Color(0, 255, 0, 255);
				break;
			case EClientClass::Jockey:
				name = "Jockey";
				color = Color(0, 255, 0, 255);
				break;
			case EClientClass::Smoker:
				name = "Smoker";
				color = Color(0, 255, 0, 255);
				break;
			case EClientClass::Hunter:
				name = "Hunter";
				color = Color(0, 255, 0, 255);
				break;
			case EClientClass::Spitter:
				name = "Spitter";
				color = Color(0, 255, 0, 255);
				break;
			case EClientClass::Charger:
			{
				name = "Charger";
                if (pBaseEntity->As<C_TerrorPlayer*>()->m_dragTarget() != nullptr)
				{
					color = Color(255, 0, 0, 255);
					break;
				}
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
			if (name == "v")
				return;
			G::Draw.String(EFonts::DEBUG, screen.x, screen.y - G::Draw.GetFontHeight(EFonts::DEBUG) - 1, color, TXT_CENTERXY, name.c_str());
		}
		void ESPHelper::onRender2D()
		{
			if (!I::EngineClient->IsInGame() || I::EngineVGui->IsGameUIVisible())
				return;

			const int nLocalIndex = I::EngineClient->GetLocalPlayer();

			C_TerrorPlayer *pLocal = I::ClientEntityList->GetClientEntity(nLocalIndex)->As<C_TerrorPlayer *>();

			if (!pLocal)
				return;
			const auto doDrawEntity = [this](std::vector<IClientEntity *> list, int classType)
			{
				if (list.size() <= 0)
					return;
				for (int i = 0; i < list.size(); i++)
				{
					this->drawESP(list[i]->GetBaseEntity(), classType == EClientClass::Tank ? HITGROUP_CHEST : HITGROUP_HEAD);
				}
			};
			// Infected, Boomer, Spitter, Charger, Smoker, Jockey, Hunter, Witch, Tank

			for (auto &[enabled, classType] : entityTypes)
			{
				if (enabled())
				{
					doDrawEntity(Utils::g_EntityCache.getEntityFromGroup(classType), classType);
				}
			}
		}
	}
}
