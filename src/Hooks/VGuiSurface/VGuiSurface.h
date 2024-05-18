#pragma once

#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace VGuiSurface
	{
		inline Hook::CTable Table;

		namespace LockCursor
		{
			using FN = void(__thiscall *)(IVGuiSurface *);
			constexpr uint32_t Index = 59u;

			void __fastcall Detour();
		}

		void Init();
	}
}