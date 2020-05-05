// Filename: safety_measures.h
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This is the header file for safety_measures.cpp


#include <windows.h>
#include <string>

// Function to find out the computer name of the executing host.
// Returns the computer name as a string.
std::string getComputerName();

// Function to generate a MD5 hash.
// Takes a pointer to char containing the data to be hashed and returns a pointer to the MD5 hash.
char* HashMD5(char* data);

// Function to check whether the executing host is the desired target or not by comparing the hashes of the computer name.
// Returns 0 if matches, otherwise 1.
int checkHost();

// Function to check whether the execution date exceeds the implant kill date or not.
// Returns 0 if date is valid, otherwise 1.
int checkDate();

// Control all the functions that ensure implant safety from here.
// Returns TRUE if host is the intended target, otherwise FALSE.
bool validateEndpoint();