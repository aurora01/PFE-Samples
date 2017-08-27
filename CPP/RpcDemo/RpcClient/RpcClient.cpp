// RpcClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void WINAPI Callback1_Proc(wchar_t * pszString);


int main()
{
    unsigned long handle;
    long lData = 0;

    RpcDemo_OpenSession(&handle);

    RpcDemo_SetCallback1(handle, Callback1_Proc);
    
    RpcDemo_HelloProc(handle, L"Hello, World....................", &lData);
    wprintf(L"\nReturned = %08x\n", lData);
    
    RpcDemo_CloseSession(handle);

    return 0;
}

void WINAPI Callback1_Proc(wchar_t * pszString)
{
    wprintf(L"\Callback1_Proc - %s\n", pszString);
}
