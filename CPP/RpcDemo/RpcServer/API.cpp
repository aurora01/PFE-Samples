#include "stdafx.h"
#include "RpcDemo_h.h"


void HelloProc(/* [string][in] */ wchar_t * pszString,  /* [out] */ long * longOut)
{
    *longOut = 0x7f7f6363L;
    wprintf(L"\nMSG:%s", pszString);
    CallbackProc(L"CallbackProc()");
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
