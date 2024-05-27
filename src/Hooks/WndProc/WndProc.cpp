#include "WndProc.h"
// #define WIN32_LEAN_AND_MEAN
#include <winuser.h>

using namespace Hooks;

LRESULT CALLBACK WndProc::Detour(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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