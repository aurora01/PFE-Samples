// RpcClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
    unsigned long handle;
    long lData = 0;

    RpcDemo_OpenSession(&handle);
    
    RpcDemo_HelloProc(handle, L"Hello, World....................", &lData);
    wprintf(L"\nReturned = %08x\n", lData);
    
    RpcDemo_CloseSession(handle);

    return 0;
}
