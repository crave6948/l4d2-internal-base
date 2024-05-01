#include "ClientMode.h"

#include "../../Client/None.h"

using namespace Hooks;

bool __fastcall ClientMode::ShouldDrawFog::Detour(void* ecx, void* edx)
{
	return Table.Original<FN>(Index)(ecx, edx);
}

bool __fastcall ClientMode::CreateMove::Detour(void* ecx, void* edx, float input_sample_frametime, CUserCmd* cmd)
{
	if (!cmd || !cmd->command_number)
		return Table.Original<FN>(Index)(ecx, edx, input_sample_frametime, cmd);

	if (Table.Original<FN>(Index)(ecx, edx, input_sample_frametime, cmd))
		I::Prediction->SetLocalViewAngles(cmd->viewangles);

	//uintptr_t _ebp; __asm mov _ebp, ebp;
	//bool* pSendPacket = (bool*)(***(uintptr_t***)_ebp - 0x1D);
	C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer*>();
	Client::client.moduleManager.onCreateMove(cmd, pLocal);

	return false;
}

void __fastcall Hooks::ClientMode::OverrideView::Detour(void* ecx, void* edx, CViewSetup* pSetup)
{
	Client::client.moduleManager.onOverrideView(pSetup);
	C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer*>();

	// // thanks lily
	// if ( true )
	// {
	// 	auto set_thirdperson_state = []( const bool& state, const bool& alive )
	// 	{
	// 		if ( alive )
	// 		{
	// 			static Vector player_view;
	// 			float dist = 50.f + 10.f;

	// 			I::EngineClient->GetViewAngles( player_view );
	// 			I::IInput->m_fCameraInThirdPerson = state;
	// 			I::IInput->m_vecCameraOffset = state ? Vector( player_view.x, player_view.y, dist ) : Vector( player_view.x, player_view.y, player_view.z );
	// 		}
	// 		else
	// 		{
	// 			I::IInput->m_fCameraInThirdPerson = false;
	// 		}
	// 	};

	// 	static bool on = false;
	// 	static bool is_clicking = false;

	// 	// toggle
	// 	{
	// 		if ( GetAsyncKeyState(0x56) & 0x8000)
	// 		{
	// 			if ( !is_clicking )
	// 				on = !on;
	// 			is_clicking = true;
	// 		}
	// 		else
	// 			is_clicking = false;
	// 	}

	// 	// update thirdperson state
	// 	set_thirdperson_state( true, true );

	// 	if ( !pLocal->deadflag() && on )
	// 	{
	// 		constexpr   float   cam_hull_offset{ 16.0f };
	// 		const       Vector    cam_hull_min( -cam_hull_offset, -cam_hull_offset, -cam_hull_offset );
	// 		const       Vector    cam_hull_max( cam_hull_offset, cam_hull_offset, cam_hull_offset );
	// 		Vector                cam_forward, origin = pLocal->Weapon_ShootPosition();

	// 		Ray_t ray;
	// 		trace_t tr;
	// 		CTraceFilterHitAll filter{pLocal};

	// 		cam_forward = U::Math.AngleVectors( Vector( I::IInput->m_vecCameraOffset.x, I::IInput->m_vecCameraOffset.y, 0.0f ) );

	// 		ray.Init( origin, origin - ( cam_forward * I::IInput->m_vecCameraOffset.z ), cam_hull_min, cam_hull_max );

	// 		I::EngineTrace->TraceRay( ray, MASK_SOLID & ~CONTENTS_MONSTER, &filter, &tr );

	// 		if ( tr.fraction < 1.0f )
	// 			I::IInput->m_vecCameraOffset.z *= tr.fraction;
	// 	}
	// }

	Table.Original<FN>(Index)(ecx, edx, pSetup);

	//pSetup->fov = 125.0f;
}

void __fastcall ClientMode::DoPostScreenSpaceEffects::Detour(void* ecx, void* edx, const void* pSetup)
{
	Table.Original<FN>(Index)(ecx, edx, pSetup);
}

float __fastcall ClientMode::GetViewModelFOV::Detour(void* ecx, void* edx)
{
	return Table.Original<FN>(Index)(ecx, edx);
}

void ClientMode::Init()
{
	XASSERT(Table.Init(I::ClientMode) == false);
	XASSERT(Table.Hook(&ShouldDrawFog::Detour, ShouldDrawFog::Index) == false);
	XASSERT(Table.Hook(&CreateMove::Detour, CreateMove::Index) == false);
	//XASSERT(Table.Hook(&OverrideView::Detour, OverrideView::Index) == false);
	XASSERT(Table.Hook(&DoPostScreenSpaceEffects::Detour, DoPostScreenSpaceEffects::Index) == false);
	XASSERT(Table.Hook(&GetViewModelFOV::Detour, GetViewModelFOV::Index) == false);
}
