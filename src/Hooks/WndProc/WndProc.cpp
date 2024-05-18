#include "WndProc.h"
#include "../../Client/None.h"
#include "../../Client/Ui/gui.h"
#include "../../ext/imgui/imgui_impl_win32.h"
#include <winuser.h>

using namespace Hooks;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND window,
    UINT message,
    WPARAM wideParam,
    LPARAM longParam);
LRESULT CALLBACK WndProc::Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
        gui::open = !gui::open;
	// if (gui::open && (I::EngineClient->Con_IsVisible() || I::EngineVGui->IsGameUIVisible()))
	if (gui::open && ImGui_ImplWin32_WndProcHandler(
                         hwnd,
                         uMsg,
                         wParam,
                         lParam))
		return 1;
	return CallWindowProcW(oWndProc, hwnd, uMsg, wParam, lParam);
}

void WndProc::Init()
{
	while (!hwGame)
	{
		hwGame = FindWindowW(L"Valve001", nullptr);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongW(hwGame, GWLP_WNDPROC, reinterpret_cast<LONG>(Detour)));
}

void WndProc::UnInitialize()
{
	SetWindowLongW(hwGame, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
}