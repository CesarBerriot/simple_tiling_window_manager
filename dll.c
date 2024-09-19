#include "dll.h"
#include <windows.h>

LRESULT CALLBACK hook_procedure(int code, WPARAM wparam, LPARAM lparam)
{	switch(code)
	{	case HSHELL_WINDOWCREATED:
		case HSHELL_WINDOWDESTROYED:
			TileWindows(NULL, MDITILE_HORIZONTAL | MDITILE_VERTICAL, NULL, 0, NULL);
		default:;
	}
	return CallNextHookEx(NULL, code, wparam, lparam);
}

HMODULE get_module_handle(void)
{	void(*pointer)(void) = (void(*)(void))get_module_handle;
	HMODULE module;
	if(GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, *(char**)&pointer, &module))
		return module;
	else
		return NULL;
}
