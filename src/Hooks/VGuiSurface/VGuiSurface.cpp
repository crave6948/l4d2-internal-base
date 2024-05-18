#include "VGuiSurface.h"
#include "../../Client/None.h"
void __fastcall Hooks::VGuiSurface::LockCursor::Detour()
{
    Client::client.menu.toggled ? I::VGuiSurface->UnlockCursor() : Table.Original<FN>(Index)(I::VGuiSurface);
}

void Hooks::VGuiSurface::Init()
{
    XASSERT(Table.Init(I::VGuiSurface) == false);
	XASSERT(Table.Hook(&LockCursor::Detour, LockCursor::Index) == false);
}