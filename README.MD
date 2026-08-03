# Windows PID Finder (C++)

A lightweight C++ utility that retrieves the Process ID (PID) of any running Windows process by its executable name. 

Built using the Windows Toolhelp API (`TlHelp32.h`).

---

## 🚀 Features

* **Case-Insensitive Matching:** Uses `_wcsicmp` to match process names regardless of uppercase/lowercase formatting.
* **Wide String Support:** Uses Unicode Win32 APIs (`Process32FirstW`, `Process32NextW`) for standard Windows system compatibility.
* **Lightweight:** Has zero third-party dependencies—only pure Windows API calls.

---

## 🛠️ Prerequisites & Requirements

* **OS:** Windows (10/11 recommended)
* **Compiler:** Any C++ compiler supporting standard Win32 headers (e.g., **MSVC** via Visual Studio, **MinGW-w64**)

---

## 📦 Building the Project

### Using Developer Command Prompt (MSVC / Visual Studio)
```cmd
cl /EHsc /W4 main.cpp /Fe:PidFinder.exe
```

### Using MinGW / GCC
```bash
g++ main.cpp -o PidFinder.exe
```

---

## 💻 Usage

1. Run the compiled executable:
   ```cmd
   .\PidFinder.exe
   ```
2. Enter the executable name of the running process, including its extension (e.g., `notepad.exe`, `discord.exe`).

### Example Output
```text
process name (Must include extension (eg .exe, .dll)): notepad.exe
PID = 14832
```

---

## ⚙️ How It Works

1. **`CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)`**: Creates a system snapshot of all currently running processes.
2. **`Process32FirstW` / `Process32NextW`**: Iterates through each process entry in the snapshot.
3. **`_wcsicmp`**: Compares the target string against each process's executable name (`szExeFile`).
4. **`CloseHandle`**: Properly disposes of the snapshot handle to avoid resource leaks.

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
