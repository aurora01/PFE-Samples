// RpcServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern RPC_STATUS RPC_Server_Initialize();
extern void RPC_Server_Shutdown(void);

int main()
{
    RPC_STATUS status;

    wprintf(L"RpcServer - Starting.........\n");
    status = RPC_Server_Initialize();
    if (RPC_S_OK != status)
    {
        wprintf(L"\nRpcServer - failed, error %08X.", status);
    }
    else
    {
        wprintf(L"\nRpcServer - Started!\nWait for client call.....");

        char line[MAX_PATH]; // room for 20 chars + '\0'  
        do
        {
            wprintf(L"\nPress \'x\' to stop:");
            gets_s(line, MAX_PATH);

        } while (line[0] != 'x' && line[0] != 'X');
        
        RPC_Server_Shutdown();
    }


    return status;
}

