#include <windows.h>
#include <stdio.h>
#include <stdnoreturn.h>
#include <stdarg.h>
#include <stdbool.h>
#include "dll.h"

#define fail_if(condition, ...) do { if(condition) fail(__VA_ARGS__); } while(false)

noreturn void fail(char format[], ...);

int main(void)
{	HMODULE dll_module = get_module_handle();
	fail_if(!dll_module, "failed to load the hook dll");
	FARPROC hook_procedure_address = GetProcAddress(dll_module, "hook_procedure");
	fail_if(!hook_procedure_address, "failed to acquire the hook procedure's address");
	HHOOK hook = SetWindowsHookExA(WH_SHELL, hook_procedure_address, dll_module, 0);
	fail_if(!hook, "hooking failed. win32 error : %lu", GetLastError());
	fflush(stdin);
	fseek(stdin, 0, SEEK_END);
	puts("type \"stop\" to unhook and exit");
	bool done = false;
	while(!done)
	{	fflush(stdin);
		char buffer[6];
		if(!fgets(buffer, 6, stdin))
			continue;
		if(!strcmp(buffer, "stop\n"))
			done = true;
		else
		{	fputs("unrecognized command. use \"stop\" to exit.\n", stderr);
			fseek(stdin, 0, SEEK_END);
		}
	}
	fail_if(!UnhookWindowsHookEx(hook), "unhooking failed with win32 error : %lu", GetLastError());
	puts("successfully unhooked");
	return EXIT_SUCCESS;
}

noreturn void fail(char format[], ...)
{	va_list arguments;
	va_start(arguments, format);
	vfprintf(stderr, format, arguments);
	fputc('\n', stderr);
	va_end(arguments);
	exit(EXIT_FAILURE);
}
