// RpcDemoClientLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SessionInfo.h"

RPCDEMOCLIENTLIB_API DWORD RpcDemo_OpenSession(unsigned long* handle)
{
    return SessionInfo::OpenSession(handle);
}

RPCDEMOCLIENTLIB_API DWORD RpcDemo_CloseSession(unsigned long handle)
{
    return SessionInfo::CloseSession(handle);
}

RPCDEMOCLIENTLIB_API void RpcDemo_HelloProc(unsigned long handle, wchar_t * pszString, long * longOut)
{
    auto pSession = SessionInfo::GetSession(handle);

    if (NULL != pSession)
    {
        pSession->API_HelloProc(pszString, longOut);
    }
}

RPCDEMOCLIENTLIB_API void RpcDemo_SetCallback1(unsigned long handle, PCALLBACK1_PROC pfnCallback)
{
    auto pSession = SessionInfo::GetSession(handle);

    if (NULL != pSession)
    {
        pSession->API_SetCallback1(pfnCallback);
    }
}
