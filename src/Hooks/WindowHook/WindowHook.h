#pragma once

#include "../../SDK/SDK.h"
#include "../../Client/Ui/gui.h"

namespace Hooks
{
	namespace WindowHook
	{
        inline Hook::CTable Table;
		namespace EndScene
		{
			using FN = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
			constexpr uint32_t Index = 42u;

			long __stdcall Detour(IDirect3DDevice9* pDevice) noexcept;
		}

        namespace Reset
        {
            using FN = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
			constexpr uint32_t Index = 16u;

			HRESULT __stdcall Detour(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params) noexcept;
        }

		void Init();
	}
}