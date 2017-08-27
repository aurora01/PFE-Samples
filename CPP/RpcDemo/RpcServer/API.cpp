#include "stdafx.h"
#include "RpcDemo_h.h"


void HelloProc(/* [string][in] */ wchar_t * pszString)
{
    wprintf(L"\nMSG:%s", pszString);
}

void Shutdown(void)
{
    RPC_STATUS status;

    status = RpcMgmtStopServerListening(NULL);

    if (status)
    {
        exit(status);
    }

    status = RpcServerUnregisterIf(NULL, NULL, FALSE);

    if (status)
    {
        exit(status);
    }
}
