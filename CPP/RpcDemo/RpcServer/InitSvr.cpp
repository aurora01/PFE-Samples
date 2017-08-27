// InitServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RpcDemo_h.h"

static WCHAR g_pszProtocolSequence[] = L"ncacn_np";
static WCHAR g_pszEndpoint[] = L"\\pipe\\hello";

RPC_STATUS RPC_Server_Initialize()
{
    RPC_STATUS status;
    RPC_WSTR pszSecurity = NULL;
    unsigned int    cMinCalls = 1;
    unsigned int    fDontWait = FALSE;

    status = RpcServerRegisterIfEx(IRpcDemo_v1_0_s_ifspec, NULL, NULL, 0, RPC_C_LISTEN_MAX_CALLS_DEFAULT, NULL);
    if (RPC_S_OK == status)
    {
        status = RpcServerUseProtseqEp(
                            (RPC_WSTR)g_pszProtocolSequence,    // _In_ RPC_WSTR Protseq
                            RPC_C_LISTEN_MAX_CALLS_DEFAULT,     // _In_ unsigned int MaxCalls
                            (RPC_WSTR)g_pszEndpoint,            // _In_ RPC_WSTR Endpoint        
                            pszSecurity);                       // _In_opt_ void __RPC_FAR * SecurityDescriptor
        if (RPC_S_OK == status)
        {
            status = RpcServerListen(cMinCalls, RPC_C_LISTEN_MAX_CALLS_DEFAULT, fDontWait);
        }
    }

    return status;
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

