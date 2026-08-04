#include <iostream>
#include <string>
#include "Process.hpp"

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
        system("pause");
        return 1;
    }
    if (pid != 0){
        std::cout << "PID = " << pid << std::endl;}

    char choice;
    std::cout << "Would you like the base adress of the program aswell?(y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        uintptr_t baseAddr = getBaseAddress(pid, processName.c_str());
        if (baseAddr != 0) {
            std::cout << "Base Address = 0x" << std::hex << baseAddr << std::endl;
        } else {
            std::cout << "Could not find the base adress!\n";
        }
        return 0;
    }
}
