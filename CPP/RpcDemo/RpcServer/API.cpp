#include "stdafx.h"
#include "RpcDemo_h.h"


void RPC_HelloProc(/* [in] */unsigned long handle, /* [string][in] */ wchar_t * pszString,  /* [out] */ long * longOut)
{
    *longOut = 0x7f7f6363L;
    wprintf(L"\nRPC_HelloProc: %s", pszString);
    CallbackProc_1(handle, L"CallbackProc_1()");
}
