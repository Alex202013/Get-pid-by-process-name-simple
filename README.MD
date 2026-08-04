# WinProcess-Lookup

Small header-only C++ helper for grabbing a process's PID and module base
address on Windows, using the classic Toolhelp32 snapshot APIs. Comes with
a tiny CLI on top.

## Files

- `Process.hpp` — the actual logic (pidByNameFunc, getBaseAddress)
- `PIDbyname.cpp` — CLI wrapper around it
- `README.md`

## Building

Needs an x64 build if you want to read base addresses of 64-bit processes.

MSVC:
```cmd
cl /EHsc /std:c++17 PIDbyname.cpp /Fe:PIDbyname.exe
```

MinGW:
```bash
g++ -m64 PIDbyname.cpp -o PIDbyname.exe
```

## Usage

```cmd
PIDbyname.exe notepad.exe
```

```
PID = 14832
Would you like the base address of the program as well? (y/n): y
Base Address = 0x7ff61a2b0000
```

No arguments, and it'll just prompt you interactively instead. `-h` / `--help`
prints usage.

## Using Process.hpp elsewhere

It's header-only, so just copy it into your project and include it:

```cpp
#include "Process.hpp"

DWORD pid = pidByNameFunc(L"notepad.exe");
if (pid != 0) {
    uintptr_t base = getBaseAddress(pid, L"notepad.exe");
}
```

## Notes

Built while learning Win32/Toolhelp32 APIs — works, but not battle-tested.
PRs/issues welcome if you spot bugs.

## License

MIT
