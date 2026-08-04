#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <cstdint>

DWORD pidByNameFunc(const wchar_t* processName){
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

uintptr_t getBaseAdress(DWORD pid, const wchar_t* modName){
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

int wmain(int argc, wchar_t* argv[]){
    DWORD pid;
    std::wstring processName;
    if (argc > 1){ // checks if there is any arguments
        if (_wcsicmp(argv[1], L"-h") == 0 ||
            _wcsicmp(argv[1], L"-help") == 0 ||
            _wcsicmp(argv[1], L"--h") == 0 ||  // -help commands
            _wcsicmp(argv[1], L"--help") == 0) {
                std::cout << "PIDbyname.exe <process_name>\n";
                std::cout << "PIDbyname.exe -h | --h | -help | --help\n\n"; //-help answers
                std::cout << "Examples:\n";
                std::cout << "PIDbyname.exe notepad.exe";
                return 0;
            }
        else {
            processName = argv[1]; //reads ARGV and sets processName to it in order for command line arguments to work
        }
    } else {
    std::wcout << "process name (Must include extension (eg .exe, .dll)): ";
    std::wcin >> processName; // gets process name from user
    }
    pid = pidByNameFunc(processName.c_str()); // transforms process name into a pid
    if (pid == 0){
        std::cout << "Invalid process name " << "\n";
        system("pause");}
    if (pid != 0){
        std::cout << "PID = " << pid << std::endl;}

    char choice;
    std::cout << "Would you like the base adress of the program aswell?(y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        uintptr_t baseAddr = getBaseAdress(pid, processName.c_str());
        if (baseAddr != 0) {
            std::cout << "Base Address = 0x" << std::hex << baseAddr << std::endl;
        } else {
            std::cout << "Could not find the base adress!\n";
        }
        return 0;
    }
}
