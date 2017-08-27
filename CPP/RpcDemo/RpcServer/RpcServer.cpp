// RpcServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern RPC_STATUS RPC_Server_Initialize();

int main()
{
    wprintf(L"RpcServer - Started!\nWait for client call.....\n");
    return RPC_Server_Initialize();
}

