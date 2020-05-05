// Filename: xor.h
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is the header file for xor.cpp


#include <windows.h>

// To decrypt a XOR-encrypted string.
// The result of the operation will be reflected back in the data argument.
void XOR(char * data, size_t data_len, char * key, size_t key_len);