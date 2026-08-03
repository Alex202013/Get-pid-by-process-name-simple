#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD pidByNameFunc(const wchar_t* processName){
    DWORD pid = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE){
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

int main(){
    DWORD pid;
    std::wstring processName;
    std::wcout << "process name (Must include extension (eg .exe, .dll)): ";
    std::wcin >> processName;
    pid = pidByNameFunc(processName.c_str());
    if (pid == 0){
        std::cout << "Invalid process name " << "\n";
        system("pause");}
    if (pid != 0){
        std::cout << "PID = " << pid << std::endl;
        return 0;
    }
}
