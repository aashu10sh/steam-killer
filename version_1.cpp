#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>

void killProcessByName(const char *filename) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapShot == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(PROCESSENTRY32);

    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes) {
        if (_stricmp(pEntry.szExeFile, filename) == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pEntry.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }

    CloseHandle(hSnapShot);
}

int main() {
const char *common_exes[] = {
        "steam.exe",
        "dota2.exe",
        "csgo.exe",
        "VALORANT.exe",
        "explorer.exe",
        NULL // Add a NULL at the end to mark the end of the array
    };

    // Loop through the array and kill each process
    for (int i = 0; common_exes[i] != NULL; i++) {
        killProcessByName((char *)common_exes[i]);
    }

    return 0;


}
