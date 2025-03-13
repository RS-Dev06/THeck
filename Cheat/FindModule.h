#pragma once

#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <vector>

inline uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

inline DWORD_PTR dwGetModuleBaseAddress(DWORD dwProcID, const wchar_t* szModuleName)
{
    DWORD_PTR dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 ModuleEntry32;
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &ModuleEntry32))
        {
            do
            {
                if (_tcsicmp(ModuleEntry32.szModule, szModuleName) == 0)
                {
                    dwModuleBaseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnapshot, &ModuleEntry32));
        }
        CloseHandle(hSnapshot);
    }
    return dwModuleBaseAddress;
}

inline uintptr_t GetPointerChainAddress(const std::vector<DWORD> baseOffsets, HANDLE processHandle, uintptr_t baseAddress)
{
    for (int i = 0; i < baseOffsets.size() - 1; i++)
    {
        ReadProcessMemory(processHandle, (LPCVOID)(baseAddress + baseOffsets.at(i)), &baseAddress, sizeof(baseAddress), nullptr);
    }
    baseAddress += baseOffsets.at(baseOffsets.size() - 1);

    return baseAddress;
}
