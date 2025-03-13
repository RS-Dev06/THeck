#include "CheatFunctions.h"

void cheatFunctions::nop_(PVOID address, int bytes)
{
    DWORD d, ds;
    VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
    memset(address, NOP, bytes); VirtualProtect(address, bytes, d, &ds);
}
