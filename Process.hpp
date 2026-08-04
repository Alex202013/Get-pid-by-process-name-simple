#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>

inline DWORD pidByNameFunc(const wchar_t* processName){
    DWORD pid = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE){ //makes sure the snapshoot is valid
        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(processEntry);
        if (Process32FirstW(hSnapshot, &processEntry)){
            do {
                if(_wcsicmp(processEntry.szExeFile, processName ) == 0){
                    pid = processEntry.th32ProcessID;
                    break;
                }
                }while (Process32NextW(hSnapshot, &processEntry));
            }
        }       CloseHandle(hSnapshot);
        return pid;
        }

inline uintptr_t getBaseAddress(DWORD pid, const wchar_t* modName){
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, pid);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W moduleEntry;
        moduleEntry.dwSize = sizeof(moduleEntry);
        if (Module32FirstW(hSnap, &moduleEntry)) {
            do {
                if (_wcsicmp(moduleEntry.szModule, modName) == 0){
                    modBaseAddr = (uintptr_t)moduleEntry.modBaseAddr;
                    break; }
                }   while (Module32NextW(hSnap, &moduleEntry));

        }
    }   CloseHandle(hSnap);
        return modBaseAddr;
}
