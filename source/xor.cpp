// Filename: xor.cpp
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is a source file which contains a function to XOR 
// the encrypted string with the appropriate key to get the original 
// string back before it is needed.


#include "xor.h"

// To decrypt a XOR-encrypted string.
// The result of the operation will be reflected back in the data argument.
void XOR(char * data, size_t data_len, char * key, size_t key_len) {
	int j;
	j = 0;
	for (int i = 0; i < data_len; i++) {
		if (j == key_len - 1) j = 0;
		data[i] = data[i] ^ key[j];
		j++;
	}
}