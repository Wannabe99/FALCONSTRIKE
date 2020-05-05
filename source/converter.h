// Filename: converter.h
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is the header file for converter.cpp


#include <string.h>
#include <malloc.h>
#include <cstdio>

// To prep the shellcode hex string received by fetcher for injection.
// Takes the shellcode hex as input and returns a shellcode byte buffer.
unsigned char* toBytes(unsigned char *buffer);