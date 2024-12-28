#include <windows.h>
#include <aclapi.h>
#include <stdio.h>
#include <sddl.h> // Might be able to remove
#include <processthreadsapi.h>
#include <tlhelp32.h>

const wchar_t* TARGET_PROCESS_NAME = L"explorer";
DWORD pid;


int wmain() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    BOOL success = Process32First(hSnapshot, &pe32);
    if (!success) {
        DWORD error = GetLastError();
        wprintf(L"FAIL!\n", error);
        CloseHandle(hSnapshot);
        return 1;
    }
    CloseHandle(hSnapshot);
    return 0;
}