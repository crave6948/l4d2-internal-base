#include "WndProc.h"
#include "../../Client/None.h"
#include <winuser.h>

using namespace Hooks;

LRESULT CALLBACK WndProc::Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (Client::client.menu.toggled && (I::EngineClient->Con_IsVisible() || I::EngineVGui->IsGameUIVisible()))
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