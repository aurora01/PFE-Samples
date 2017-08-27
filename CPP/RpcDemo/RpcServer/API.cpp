#include "stdafx.h"
#include "RpcDemo_h.h"


void RPC_HelloProc(/* [in] */unsigned long handle, /* [string][in] */ wchar_t * pszString,  /* [out] */ long * longOut)
{
    *longOut = 0x7f7f6363L;
    wprintf(L"\RPC_HelloProc: %s", pszString);
    CallbackProc_1(handle, L"CallbackProc_1()");
}

void RPC_Shutdown(void)
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
