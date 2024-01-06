#include "Manager.h"
#include "RotationManager.h"

namespace F {
	void Manager::onRender2D()
	{
		ESP.Render();
		for (Module* mod : featurelist) {
			if (!mod->getEnabled()) continue;
			mod->onRender2D();
		}
		if (!I::EngineClient->IsInGame()) {
			return;
		};
		if (I::EngineVGui->IsGameUIVisible()) { return; }
		C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer*>();
		if (!Helper::rotationManager.getCurrentRotation().IsZero())
		{
			Vector vec = U::Math.AngleVectors(Helper::rotationManager.getCurrentRotation());
			Vector vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * 1400.0f);
			Vector screen;
			G::Util.W2S(vViewAngleOnWorld, screen);

			int screenW = G::Draw.m_nScreenW, screenH = G::Draw.m_nScreenH;

			if (Helper::rotationManager.DisabledRotation) {
				screenW = screenW / 2;
				screenH = screenH / 2;
				G::Draw.Line(screenW, screenH, screenW - 4, screenH + 4, Color(255, 255, 255, 255));
				G::Draw.Line(screenW, screenH, screenW + 4, screenH + 4, Color(255, 255, 255, 255));
				screenW = screenW * 2;
				screenH = screenH * 2;
			}
			else {
				G::Draw.Line(screen.x, screen.y, screen.x - 4, screen.y + 4,Color(255, 255, 255, 255));
				G::Draw.Line(screen.x, screen.y, screen.x + 4, screen.y + 4, Color(255, 255, 255, 255));
			}
			//G::Draw.Circle(screen.x, screen.y, 2, 8, );
		}
	}

	void Manager::Init()
	{
		featurelist.push_back(bhop_ptr);
		featurelist.push_back(arraylist_ptr);
		featurelist.push_back(aimbot_ptr);
		featurelist.push_back(noSpread_ptr);
		featurelist.push_back(espHelper_ptr);
	}

	void Manager::onCreateMove(CUserCmd* cmd, C_TerrorPlayer* pLocal)
	{
		if (pLocal && !pLocal->deadflag())
		{
			C_TerrorWeapon* pWeapon = pLocal->GetActiveWeapon()->As<C_TerrorWeapon*>();
			Vector oldViewangles = cmd->viewangles;

			for (Module* mod : featurelist) {
				if (!mod->getEnabled()) continue;
				if (mod->getName() == "NoSpread") continue;
				mod->onPreCreateMove(cmd, pWeapon, pLocal);
			}
			Helper::rotationManager.onUpdate(pLocal);
			if (!Helper::rotationManager.getCurrentRotation().IsZero() && !Helper::rotationManager.DisabledRotation) {
				cmd->viewangles = Helper::rotationManager.getCurrentRotation();
				//I::EngineClient->SetViewAngles(cmd->viewangles);
			}
			for (Module* mod : featurelist) {
				if (!mod->getEnabled()) continue;
				mod->onPostCreateMove(cmd, pWeapon, pLocal);
			}
			if (pWeapon)
			{
				F::EnginePrediction.Start(pLocal, cmd);
				{
					for (Module* mod : featurelist) {
						if (mod->getName() != "NoSpread") continue;
						if (!mod->getEnabled()) continue;
						mod->onPreCreateMove(cmd, pWeapon, pLocal);
					}
				}
				F::EnginePrediction.Finish(pLocal, cmd);
			}
			G::Util.FixMovement(oldViewangles,cmd);
		}
	}

	void Manager::onKey()
	{
		//bool isToggled = keyState & 1;
		//bool isDown = keyState & 0x8000;
		if (!I::EngineClient->IsInGame() || I::EngineClient->IsPaused()) return;
		for (Module* mod : featurelist) {
			if (GetAsyncKeyState(mod->getKey()) & 0x8000)
			{
				if (!mod->ShouldToggle()) continue;
				mod->toggle();
				mod->keytimeout = 1;
			}
			else {
				if (mod->keytimeout > 0)
					mod->keytimeout--;
			}
		}
	}
}
