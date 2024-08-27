#include <process.h>
#include <tlhelp32.h>
#include <winbase.h>
#include <windows.h>

#include <string.h>
void killProcessByName(const char *filename) {
  HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
  PROCESSENTRY32 pEntry;
  pEntry.dwSize = sizeof(pEntry);
  BOOL hRes = Process32First(hSnapShot, &pEntry);
  while (hRes) {
    if (strcmp(pEntry.szExeFile, filename) == 0) {
      HANDLE hProcess =
          OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
      if (hProcess != NULL) {
        TerminateProcess(hProcess, 9);
        CloseHandle(hProcess);
      }
    }
    hRes = Process32Next(hSnapShot, &pEntry);
    CloseHandle(hSnapShot);
  }
}
int main() {
  const char *common_exes[] = {"dota2.exe",
                               "steam.exe",
                               "VALORANT.exe",
                               "csgo.exe",
                               "League of Legends.exe",
                               NULL};

  for (int i = 0; common_exes[i] != NULL; i++) {
    killProcessByName(common_exes[i]);
  }
  return 0;
}
