// Filename: injector.h
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is the header file for injector.cpp


#include <windows.h>
#include <winternl.h>
#include <string>

#pragma comment(lib, "ntdll") // -lntdll

// Test function to test the shellcode by executing it in-memory.
// Takes the shellcode byte buffer as input.
void executeShellcode(unsigned char* shellcode);

// AddressOfEntryPoint shellcode injection without VirtualAllocEx RWX.
// Takes the shellcode byte buffer and shellcode length as input.
void addressOfEntryPointInjection(unsigned char* shellcode, int shellcode_len);