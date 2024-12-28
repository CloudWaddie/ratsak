#include <windows.h>
#include <aclapi.h>
#include <stdio.h>
#include <sddl.h>
#include <processthreadsapi.h>
#include <tlhelp32.h>


DWORD pid;


int wmain(int argc, wchar_t* argv[]) {
    wchar_t TARGET_PROCESS_NAME[MAX_PATH];
    if (argc != 2) {
        wprintf(L"Usage: %ls <process name>\n", argv[0]);
        return 1;
    }
    wcscpy_s(TARGET_PROCESS_NAME, MAX_PATH, argv[1]);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    BOOL success = Process32First(hSnapshot, &pe32);
    if (!success) {
        DWORD error = GetLastError();
        wprintf(L"FAIL! Error: ", error);
        CloseHandle(hSnapshot);
        return 1;
    }
    if (wcscmp(pe32.szExeFile, TARGET_PROCESS_NAME) == 0) {
        printf("FOUND PROCESS!");
    };
    while (Process32Next(hSnapshot, &pe32)) {
        if (wcscmp(pe32.szExeFile, TARGET_PROCESS_NAME) == 0) {
            printf("FOUND PROCESS! PID: %d EXE: %ls\n", pe32.th32ProcessID, pe32.szExeFile);
            CloseHandle(hSnapshot);
            return 0;
        };
    }

    wprintf(L"Process %ls not found.\n", TARGET_PROCESS_NAME);
    CloseHandle(hSnapshot);
    
    return 0;
}