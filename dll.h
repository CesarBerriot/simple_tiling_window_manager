#include <windef.h>

LRESULT CALLBACK hook_procedure(int code, WPARAM wparam, LPARAM lparam);

HMODULE get_module_handle(void);
