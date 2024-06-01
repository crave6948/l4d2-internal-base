#include "Entry/Entry.h"

DWORD APIENTRY MainThread(LPVOID lpParam)
{
	G::ModuleEntry.Load();

	while (!G::ModuleEntry.ShouldUnload())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	G::ModuleEntry.Unload();
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (const auto hMain = CreateThread(0, 0, MainThread, hinstDLL, 0, 0))
			CloseHandle(hMain);

		break;
	}
	default:
		break;
	}

	return TRUE;
}