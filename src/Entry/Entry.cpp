#include "Entry.h"
#pragma once
#include "../Client/None.h"

#include <cstdint>

void CGlobal_ModuleEntry::Load()
{
	while (!GetModuleHandleA("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::seconds(1));

	U::Offsets.Init();
	// Interfaces
	{
		I::BaseClient = U::Interface.Get<IBaseClientDLL *>("client.dll", "VClient016");
		I::ClientEntityList = U::Interface.Get<IClientEntityList *>("client.dll", "VClientEntityList003");
		I::Prediction = U::Interface.Get<IPrediction *>("client.dll", "VClientPrediction001");
		I::GameMovement = U::Interface.Get<IGameMovement *>("client.dll", "GameMovement001");

		I::EngineClient = U::Interface.Get<IVEngineClient *>("engine.dll", "VEngineClient013");
		I::EngineTrace = U::Interface.Get<IEngineTrace *>("engine.dll", "EngineTraceClient003");
		I::EngineVGui = U::Interface.Get<IEngineVGui *>("engine.dll", "VEngineVGui001");
		I::RenderView = U::Interface.Get<IVRenderView *>("engine.dll", "VEngineRenderView013");
		I::DebugOverlay = U::Interface.Get<IVDebugOverlay *>("engine.dll", "VDebugOverlay003");
		I::ModelInfo = U::Interface.Get<IVModelInfo *>("engine.dll", "VModelInfoClient004");
		I::ModelRender = U::Interface.Get<IVModelRender *>("engine.dll", "VEngineModel016");

		I::VGuiPanel        = U::Interface.Get<IVGuiPanel*>("vgui2.dll", "VGUI_Panel009");
		I::VGuiSurface      = U::Interface.Get<IVGuiSurface*>("vgui2.dll", "VGUI_Surface031");
		I::VGuiInput = U::Interface.Get<IVGuiInput*>("vgui2.dll", "VGUI_InputInternal001");

		I::MatSystemSurface = U::Interface.Get<IMatSystemSurface *>("vguimatsurface.dll", "VGUI_Surface031");

		I::MaterialSystem = U::Interface.Get<IMaterialSystem *>("materialsystem.dll", "VMaterialSystem080");

		I::Cvar = U::Interface.Get<ICvar *>("vstdlib.dll", "VEngineCvar007");

		{
			I::ClientMode = **reinterpret_cast<void ***>(U::Offsets.m_dwClientMode);
			XASSERT(I::ClientMode == nullptr);

			I::GlobalVars = **reinterpret_cast<CGlobalVarsBase ***>(U::Offsets.m_dwGlobalVars);
			XASSERT(I::GlobalVars == nullptr);

			I::MoveHelper = **reinterpret_cast<IMoveHelper ***>(U::Offsets.m_dwMoveHelper);
			XASSERT(I::MoveHelper == nullptr);

			I::IInput = **reinterpret_cast<IInput_t ***>(U::Offsets.m_dwIInput);
			XASSERT(I::IInput == nullptr);
		}
	}

	Client::client.initialize();
	G::Draw.Init();
	try
	{

		gui::Setup();
		G::Hooks.Init();
	}
	catch (const std::exception &error)
	{
		MessageBeep(MB_ICONERROR);
		MessageBox(
			0,
			error.what(),
			"ImGui Error",
			MB_OK | MB_ICONEXCLAMATION);
		Unload();
	}
}

void CGlobal_ModuleEntry::Unload()
{
	XASSERT(MH_Uninitialize() != MH_STATUS::MH_OK);
	Hooks::WndProc::UnInitialize();
	gui::Destroy();
	Client::client.shutdown();

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool CGlobal_ModuleEntry::ShouldUnload()
{
	return GetAsyncKeyState(VK_END) & 0x8000;
}