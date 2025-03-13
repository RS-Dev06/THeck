#pragma once
#include <windows.h>

#define NOP 0x90

namespace cheatFunctions {
    void nop_(PVOID address, int bytes);
}