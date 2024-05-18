#include "WindowHook.h"

#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/imgui_impl_dx9.h"
#include "../../ext/imgui/imgui_impl_win32.h"

#include <stdexcept>
#include <intrin.h>

namespace Hooks::WindowHook
{
    long __stdcall EndScene::Detour(IDirect3DDevice9 *pDevice) noexcept
    {
        static const auto returnAddress = _ReturnAddress();

        const auto result = Table.Original<FN>(EndScene::Index)(pDevice, pDevice);

        if (_ReturnAddress() == returnAddress)
            return result;

        if (!gui::setup)
            gui::SetupMenu(pDevice);

        if (gui::open)
            gui::Render();
        return result;
    }
    HRESULT __stdcall Reset::Detour(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *params) noexcept
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        const auto result = Table.Original<FN>(Index)(pDevice, pDevice, params);
        ImGui_ImplDX9_CreateDeviceObjects();
        return result;
    }
    void Init()
    {
        XASSERT(Table.Init(gui::device) == false);
        XASSERT(Table.Hook(&EndScene::Detour, EndScene::Index) == false);
        XASSERT(Table.Hook(&Reset::Detour, Reset::Index) == false);
    }
}
