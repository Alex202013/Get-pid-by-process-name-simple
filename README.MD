# Windows PID Finder (C++)

A lightweight C++ utility that retrieves the Process ID (PID) of any running Windows process by its executable name. 

Built using native Win32 APIs (`TlHelp32.h`), it supports direct **Command-Line Arguments (CLI)**, a **Help Banner**, and an **Interactive Mode**.

---

## 🚀 Features

* **CLI & Interactive Modes:** Pass the process name directly as an argument or let the app prompt you interactively.
* **Built-in Help System:** Easily check usage and examples using `-h`, `-help`, `--h`, or `--help`.
* **Case-Insensitive Matching:** Uses `_wcsicmp` to match process names and flags regardless of uppercase/lowercase formatting.
* **Wide String Support:** Uses Unicode Win32 APIs (`wmain`, `Process32FirstW`, `Process32NextW`) for standard Windows system compatibility.
* **Lightweight:** Has zero third-party dependencies—only pure Windows API calls.

---

## 🛠️ Prerequisites & Requirements

* **OS:** Windows (10/11 recommended)
* **Compiler:** Any C++ compiler supporting standard Win32 headers (e.g., **MSVC** via Visual Studio, **MinGW-w64**)

---

## 📦 Building the Project

### Using Developer Command Prompt (MSVC / Visual Studio)
```cmd
cl /EHsc /W4 main.cpp /Fe:PIDbyname.exe
```

### Using MinGW / GCC
```bash
g++ main.cpp -o PIDbyname.exe
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
```

---

## ⚙️ How It Works

1. **`wmain(int argc, wchar_t* argv[])`**: Checks `argc` for command-line inputs. If a help flag (`-h`, `--help`, etc.) is passed, it displays the usage banner and exits. Otherwise, it uses `argv[1]` as the target process name. If `argc == 1`, it prompts the user interactively.
2. **`CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)`**: Creates a system snapshot of all currently running processes.
3. **`Process32FirstW` / `Process32NextW`**: Iterates through each process entry in the snapshot.
4. **`_wcsicmp`**: Compares the target string against each process's executable name (`szExeFile`).
5. **`CloseHandle`**: Properly disposes of the snapshot handle to avoid resource leaks.

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
