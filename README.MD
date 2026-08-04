# Windows PID & Base Address Finder (C++)

A lightweight C++ utility that retrieves the Process ID (PID) and Base Address of any running Windows process or module by its executable name. 

Built using native Win32 APIs (`TlHelp32.h`), it supports direct **Command-Line Arguments (CLI)**, a **Help Banner**, and an **Interactive Mode**.

---

## 🚀 Features

* **CLI & Interactive Modes:** Pass the process name directly as an argument or let the app prompt you interactively.
* **Base Address Inspection:** Easily fetch the module base address (in hexadecimal) for reverse engineering and memory analysis.
* **x64 Compatible:** Reads module layouts for both 64-bit and 32-bit processes when built targeting 64-bit architecture.
* **Built-in Help System:** Easily check usage and examples using `-h`, `-help`, `--h`, or `--help`.
* **Case-Insensitive Matching:** Uses `_wcsicmp` to match process names and flags regardless of uppercase/lowercase formatting.
* **Wide String Support:** Uses Unicode Win32 APIs (`wmain`, `Process32FirstW`, `Process32NextW`, `Module32FirstW`, `Module32NextW`) for standard Windows system compatibility.
* **Lightweight:** Has zero third-party dependencies—only pure Windows API calls.

---

## 🛠️ Prerequisites & Requirements

* **OS:** Windows (10/11 recommended)
* **Compiler:** Any C++ compiler supporting standard Win32 headers (e.g., **MSVC** via Visual Studio, **MinGW-w64**)

---

## 📦 Building the Project

> **Note:** To retrieve the base address of 64-bit processes (like `mspaint.exe`), compile as an **x64** binary.

### Using Developer Command Prompt (MSVC / Visual Studio)
Run from the **x64 Native Tools Command Prompt**:
```cmd
cl /EHsc /std:c++17 main.cpp /Fe:PIDbyname.exe
```

### Using MinGW / GCC
```bash
g++ -m64 main.cpp -o PIDbyname.exe
```

---

## 💻 Usage

### 1. Command-Line Argument (Fastest)
Pass the executable name directly when launching the app:

```cmd
.\PIDbyname.exe notepad.exe
```

**Output:**
```text
PID = 14832
Would you like the base address of the program as well? (y/n): y
Base Address = 0x7ff61a2b0000
```

### 2. Help Menu
Display usage information and examples:

```cmd
.\PIDbyname.exe -h
```

**Output:**
```text
PIDbyname.exe <process_name>
PIDbyname.exe -h | --h | -help | --help

Examples:
PIDbyname.exe notepad.exe
```

### 3. Interactive Mode
If launched without arguments (or by double-clicking), the program will ask for input:

```cmd
.\PIDbyname.exe
```

**Output:**
```text
process name (Must include extension (eg .exe, .dll)): notepad.exe
PID = 14832
Would you like the base address of the program as well? (y/n): y
Base Address = 0x7ff61a2b0000
```

---

## ⚙️ How It Works

1. **`wmain(int argc, wchar_t* argv[])`**: Checks `argc` for command-line inputs. If a help flag (`-h`, `--help`, etc.) is passed, it displays the usage banner and exits. Otherwise, it uses `argv[1]` as the target process name. If `argc == 1`, it prompts the user interactively.
2. **`pidByNameFunc`**: Uses `CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)` to create a system snapshot of all currently running processes, iterating via `Process32FirstW` / `Process32NextW`.
3. **`getBaseAdress`**: Uses `CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, pid)` to scan module entries (`Module32FirstW` / `Module32NextW`) and return the module base pointer.
4. **`_wcsicmp`**: Compares the target string against each process/module name regardless of case sensitivity.
5. **`CloseHandle`**: Properly disposes of snapshot handles to avoid resource leaks.

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
